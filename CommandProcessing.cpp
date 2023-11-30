#include <string>
#include <vector>
#include <iostream>
#include <istream>
#include <fstream>
#include "CommandProcessing.h"

using namespace std;

// Default constructor
Command::Command(string commandStr) : commandStr(commandStr)
{
}

// Constructors assigning a enum type for commands that are valid
Command::Command(commandType command, string addition)
{
	switch (command)
	{
	case commandType::loadmap:
		commandStr = "loadmap";
		this->addition = addition;
		commandNumber = 0;
		break;
	case commandType::validatemap:
		commandStr = "validatemap";
		commandNumber = 1;
		break;
	case commandType::addplayer:
		commandStr = "addplayer";
		this->addition = addition;
		commandNumber = 2;
		break;
	case commandType::gamestart:
		commandStr = "gamestart";
		commandNumber = 3;
		break;
	case commandType::replay:
		commandStr = "replay";
		commandNumber = 4;
		break;
	case commandType::quit:
		commandStr = "quit";
		commandNumber = 5;
		break;
	case commandType::tournament:
		commandStr = "tournament";
		this->addition = addition;
		commandNumber = 6;
		break;
	}
}

// Copy constructor
Command::Command(const Command &command) : commandStr(command.commandStr), effect(command.effect), addition(command.addition), commandNumber(command.commandNumber) {}

// Overloading the assignment operator
Command &Command::operator=(const Command &command)
{
	this->commandStr = command.commandStr;
	this->commandNumber = command.commandNumber;
	this->effect = command.effect;
	this->addition = command.addition;

	return *this;
}

// Saves a string effect depending on which type of command it is
void Command::saveEffect(Command *command)
{

	// Switch chase to save the effect of valid commands
	switch (command->commandNumber)
	{
	case 0:
		command->effect = command->addition + " has been successfully loaded";
		break;
	case 1:
		command->effect = "The map has been validated";
		break;
	case 2:
		command->effect = "Player " + command->addition + " has been successfully added to the game";
		break;
	case 3:
		command->effect = "The game has started";
		break;
	case 4:
		command->effect = "Replaying the game";
		break;
	case 5:
		command->effect = "Quitting the game";
		break;
	/*
	case 6:
		command->effect = "Command for testing purposes that skips the main game loop";
		break;
	*/
	case 6:
		command->effect = "Entering tournament mode: " + command->addition;
		break;
	}
}

// Getter for the command entered
string Command::getCommandStr()
{
	return commandStr;
}

// Sets the commands with a specific format
void Command::setCommandStr()
{
	this->commandStr = this->commandStr + "<" + this->addition + ">";
}

// Getter for the effect
string Command::getEffect() 
{
	return effect;
}

// Getter for the addition to the command entered
string Command::getAddition()
{
	return addition;
}

// stringToLog implementation for ILoggable
// string Command::stringToLog()
// {
// 	string command = "Command issued: " + getcommandStr() + "\nCommand's effect: " + getEffect();
// 	return command;
// }

// Overloading the output operator
ostream &operator<<(ostream &out, const Command &command)
{
	return out << "Command: " << command.commandStr << command.addition << " | Effect: " << command.effect << '\n';
}

//Default constructor
CommandProcessor::CommandProcessor() {
	
}

// Copy constructor
CommandProcessor::CommandProcessor(const CommandProcessor &cmdPro) : exitProgram(cmdPro.exitProgram), cmdProPause(cmdPro.cmdProPause)
{
	for (int i = 0; i < cmdPro.commandList.size(); i++)
	{
		commandList.push_back(cmdPro.commandList[i]);
	}

	for (int i = 0; i < cmdPro.validCommandList.size(); i++)
	{
		commandList.push_back(cmdPro.validCommandList[i]);
	}
}

// Overloading the assignment operator
CommandProcessor &CommandProcessor::operator=(const CommandProcessor &cmdPro)
{
	// this->logger = cmdPro.logger;
	this->commandList = cmdPro.commandList;
	this->validCommandList = cmdPro.validCommandList;
	this->exitProgram = cmdPro.exitProgram;
	this->cmdProPause = cmdPro.cmdProPause;

	return *this;
}

// Destructor for CommandProcessor
CommandProcessor::~CommandProcessor()
{
//delete destrcut the object
}

// Reads the command from the console
Command *CommandProcessor::readCommand()
{
	string commandStr{};
	string addition{};
	int index{};

	cin >> commandStr;

	// When the commandProcessor reads the following commands, it prompts the user to give more information
	if (commandStr == "loadmap")
	{
		cout << "Which map do you wish to load? ";
		cin >> addition;
		cout << '\n';
	}
	else if (commandStr == "addplayer")
	{
		cout << "Which player do you wish to add? ";
		cin >> addition;
		cout << '\n';
	}
	
	else if (commandStr == "gamestart")
	{
		setcmdProPause(true);
	}

	if (commandStr == "tournament") {
		cout << "Enter tournament parameters: ";
		//maybe need to add something here
		getline(cin, addition); // read the entire line after the command
		cout <<'\n';
	}

	// Switch case to decide which command object to create based on the user's input
	switch (getIndexCmdVector(commandStr))
	{
	case 0:
		return new Command(Command::commandType::loadmap, addition);
	case 1:
		return new Command(Command::commandType::validatemap, addition);
	case 2:
		return new Command(Command::commandType::addplayer, addition);
	case 3:
		return new Command(Command::commandType::gamestart, addition);
	case 4:
		return new Command(Command::commandType::replay, addition);
	case 5:
		return new Command(Command::commandType::quit, addition);
	case 6:
		return new Command(Command::commandType::tournament, addition);

	default:
		// If none of the valid commands are read then the default constructor with the user's input is called
		return new Command(commandStr);
	}
}

// getCommand reads the command, validates it and saves the command
void CommandProcessor::getCommand(GameEngine *game, CommandProcessor *cmd)
{
	Command *command = cmd->readCommand();

	// If the command is valid we save it in both the valid commands vector and the general vector
	if (validate(command, game))
	{
		saveValidCommand(command);
	}

	saveCommand(command);
}

// Validates the method and work on the transition of the game
bool CommandProcessor::validate(Command *command, GameEngine *game)
{

	string userCommand = command->getCommandStr();
	string currentSate = game->getCurrentState();

	if ((userCommand == "loadmap" && currentSate == "start") || (userCommand == "loadmap" && currentSate == "maploaded"))
	{
		cout << userCommand << " is valid in the state: " << currentSate; 
		game->update(userCommand); return true;
	}
	else if (userCommand == "validatemap" && currentSate == "maploaded")
	{
		cout << userCommand << " is valid in the state: " << currentSate; 
		game->update(userCommand); return true;
	}
	else if ((userCommand == "addplayer" && currentSate == "mapvalidated") || (userCommand == "addplayer" && currentSate == "playersadded"))
	{
		cout << userCommand << " is valid in the state: " << currentSate;
		game->update(userCommand); return true;
	}
	else if (userCommand == "gamestart" && currentSate == "playersadded")
	{
		cout << userCommand << " is valid in the state: " << currentSate;
		game->update(userCommand); return true;
	}
	else if (userCommand == "replay" && currentSate == "win")
	{
		cout << userCommand << " is valid in the state: " << currentSate;
		game->update(userCommand); return true;
	} 
	else if (userCommand == "quit" && currentSate == "win")
	{
		cout << userCommand << " is valid in the state: " << currentSate;
		game->update(userCommand); return true;
	}

	else if (userCommand == "tournament" && currentSate == "start") {
		//still need to implement the logic to check the correct input here 
		cout << userCommand << " is valid in the state: " << currentSate;

		game->update(userCommand); return true;
	}

	else
	{
		if (this->getIndexCmdVector(userCommand) == -1)
		{
			cout << "Invalid command"; return false;
		}
		else
		{
			cout << userCommand << " is not a vlalid command in this state"; return false;
		}
	}
}

// Saves the command in the general command list
void CommandProcessor::saveCommand(Command *command)
{
	commandList.push_back(command);
}

// Saves the command in the valid command list
void CommandProcessor::saveValidCommand(Command *command)
{
	validCommandList.push_back(command);
}

// Gets the vector of the general command list
vector<Command *> CommandProcessor::getCommandList()
{
	return commandList;
}

// Gets the vector of the valid command list
vector<Command *> CommandProcessor::getValidCommandList()
{
	return validCommandList;
}

// Changes the string commandStr to an integer
int CommandProcessor::getIndexCmdVector(string commandStr)
{
	for (int i = 0; i < commandVector.size(); i++)
	{
		if (commandVector[i] == commandStr)
		{
			return i;
		}
	}

	return -1;
}

// Returns bool exitProgram (if true = the program stops)
bool CommandProcessor::getExitProgram()
{
	return exitProgram;
}

// Sets the bool cmdProPause (if true = the cmdPro is paused
void CommandProcessor::setcmdProPause(bool isPaused)
{
	cmdProPause = isPaused;
}

// Gets the bool cmdProPause
bool CommandProcessor::getcmdProPause()
{
	return cmdProPause;
}

// // stringToLog implementation for ILoggable
// string CommandProcessor::stringToLog()
// {
// 	return "Inserted command: " + commandList.back()->getcommandStr() + " into the list.";
// }

// Overloading the output operator
ostream &operator<<(ostream &out, const vector<Command *> &commandList)
{
	out << "\n[ ";
	for (int i = 0; i < commandList.size(); i++)
	{
		out << "\nCommand: " + commandList[i]->getCommandStr() + " || Effect: " + commandList[i]->getEffect();
		if (i != commandList.size() - 1)
			out << ", ";
	}
	out << " \n]\n";

	return out;
}

// Default constructor
FileLineReader::FileLineReader() {}

// Copy constructor
FileLineReader::FileLineReader(const FileLineReader &fileReader)
{
	for (int i = 0; i < fileReader.fileContent.size(); i++)
	{
		fileContent.push_back(fileReader.fileContent[i]);
	}
}

// Overloading the assignment operator
FileLineReader &FileLineReader::operator=(const FileLineReader &fileReader)
{
	this->fileContent = fileReader.fileContent;

	return *this;
}

// Reading from the file
void FileLineReader::readLineFromFile(string fileName)
{
	vector<string> lines;
	fileName = fileName + ".txt";
	ifstream myfile(fileName);

	// If the file is open we can read from it
	if (myfile.is_open())
	{
		string line;

		// While the file contains something we add each line to the lines vector
		while (getline(myfile, line))
		{
			lines.push_back(line);
		}

		// Closing the file
		myfile.close();

		// Copying the lines vector into the fileContent vector
		for (int i = 0; i < lines.size(); i++)
		{
			fileContent.push_back(lines[i]);
		}
	}
	else
	{
		cout << "Couldn't find the mentioned file." << '\n';
	}
}

// Returns the vector containing every line in the file read
vector<string> FileLineReader::getFileContent()
{
	return fileContent;
}

// Overloading the output operator
ostream &operator<<(ostream &out, const vector<string> lines)
{
	out << "\n[ ";
	for (int i = 0; i < lines.size(); i++)
	{
		out << "\n" + lines[i];
		if (i != lines.size() - 1)
			out << ", ";
	}
	out << " \n]\n";

	return out;
}

// Default constructor
FileCommandProcessorAdapter::FileCommandProcessorAdapter(FileLineReader *flr) : flr(flr)
{
	for (int i = 0; i < flr->getFileContent().size(); i++)
	{
		commands.push_back(flr->getFileContent().at(i));
	}
}

// Copy constructor
FileCommandProcessorAdapter::FileCommandProcessorAdapter(const FileCommandProcessorAdapter &fileAdapter) : flr(fileAdapter.flr), index(fileAdapter.index)
{
	for (int i = 0; i < flr->getFileContent().size(); i++)
	{
		commands.push_back(flr->getFileContent().at(i));
	}
}

// Overloading the assignment operator
FileCommandProcessorAdapter &FileCommandProcessorAdapter::operator=(const FileCommandProcessorAdapter &fileAdapter)
{
	this->flr = fileAdapter.flr;
	this->index = fileAdapter.index;

	for (int i = 0; i < flr->getFileContent().size(); i++)
	{
		commands.push_back(flr->getFileContent().at(i));
	}

	return *this;
}

// Destructor
FileCommandProcessorAdapter::~FileCommandProcessorAdapter()
{
	flr = nullptr;
}

// Returns a pointer to the fileLineReader
FileLineReader *FileCommandProcessorAdapter::getFileLineReader()
{
	return flr;
}

// readCommand method adapter
Command *FileCommandProcessorAdapter::readCommand()
{
	string addition{""};

	// Using a space delimiter when reading from a file for lines such as "loadmap mapname"
	string delimiter{" "};

	// The position of the delimiter
	size_t pos{};

	// The word before the delimiter
	string firstWord{""};

	// The word after the delimiter
	string secondWord{""};

	// Increasing the index of the line
	index++;

	// If the delimiter is found and is not at the end of the string
	if (commands[index].find(delimiter) != string::npos)
	{

		// Separating every line at the delimiter " " into two words
		pos = commands[index].find(delimiter);
		string firstWord(commands[index].substr(0, pos));
		string secondWord(commands[index].substr(pos + 1));

		if (firstWord == "loadmap")
		{
			return new Command(Command::commandType::loadmap, secondWord);
		}
		else if (firstWord == "addplayer")
		{
			return new Command(Command::commandType::addplayer, secondWord);
		}
		// else if (firstWord == "tournament")
		// {
		// 	return new Command(Command::commandType::tournament, secondWord);
		// }
	}

	// If the delimiter is not found then we can read the line normally
	else if (commands[index] == "validatemap")
	{
		return new Command(Command::commandType::validatemap, addition);
	}
	else if (commands[index] == "gamestart")
	{
		setcmdProPause(true);
		return new Command(Command::commandType::gamestart, addition);
	}
	else if (commands[index] == "replay")
	{
		return new Command(Command::commandType::replay, addition);
	}
	else if (commands[index] == "quit")
	{
		return new Command(Command::commandType::quit, addition);
	}
	// else if (commands[index] == "gameend")
	// {
	// 	return new Command(Command::commandType::gameend, addition);
	// }
	else
	{
		return new Command(commands[index]);
	}
}
