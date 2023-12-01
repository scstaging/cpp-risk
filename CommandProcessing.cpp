#include <string>
#include <vector>
#include <iostream>
#include <istream>
#include <fstream>
#include "CommandProcessing.h"
#include <sstream>


using namespace std;

Command::Command()
{
}

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
	// case 6:
	// 	command->effect = "Command for testing purposes that skips the main game loop";
	// 	break;
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

// Overloading the output operator
ostream &operator<<(ostream &out, const Command &command)
{
	return out << "Command: " << command.commandStr << command.addition << " | Effect: " << command.effect << '\n';
}

// Default constructor
CommandProcessor::CommandProcessor()
{
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
	// delete destrcut the object
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
	else if (commandStr == "tournament")
	{
		//not sure cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore the leftover newline
		cout << "Enter tournament command: ";
		getline(cin, addition); // Read the entire command line input

		istringstream iss(addition); // Use istringstream for parsing
		string token; // Variable to hold each token

		vector<string*> mapFiles; // Vector to store map file names
		vector<string*> playerStrategies; // Vector to store player strategies
		int numberOfGames = 0; // Variable to store number of games
		int maxNumberOfTurns = 0; // Variable to store maximum number of turns

		// Loop through each token in the input string
		while (iss >> token) {
			if (token == "-M") {
				// Parse map files list
				string maps;
				iss.ignore(2); // Ignore '<'
				getline(iss, maps, '>'); // Read until '>'
				istringstream mapStream(maps); // Stream for parsing maps
				string map;
				while (getline(mapStream, map, ',')) { // Parse each map
					string* ptrMap = new string(map);
					mapFiles.push_back(ptrMap);
				}
			} else if (token == "-P") {
				// Parse player strategies list
				string strategies;
				iss.ignore(2); // Ignore '<'
				getline(iss, strategies, '>'); // Read until '>'
				istringstream strategyStream(strategies); // Stream for parsing strategies
				string strategy;
				while (getline(strategyStream, strategy, ',')) { // Parse each strategy
					string* ptrStrategy = new string(strategy);
					playerStrategies.push_back(ptrStrategy);
				}
			} else if (token == "-G") {
				// Parse number of games
				iss.ignore(2); // Ignore '<'
				iss >> numberOfGames; // Read number of games
				iss.ignore(); // Ignore '>'
			} else if (token == "-D") {
				// Parse maximum number of turns
				iss.ignore(2); // Ignore '<'
				iss >> maxNumberOfTurns; // Read max number of turns
				iss.ignore(); // Ignore '>'
			}
		}

		return new Tournament(mapFiles,playerStrategies,numberOfGames,maxNumberOfTurns);

		// TODO: Use mapFiles and playerStrategies as needed

		// IMPORTANT: Remember to deallocate the memory later
		// for (auto ptr : mapFiles) { delete ptr; }
		// for (auto ptr : playerStrategies) { delete ptr; }


		// Output parsed data (for verification)
		cout << "Maps: ";
		for (const auto& map : mapFiles) cout << *map << " "; // Dereference the pointer
		cout << "\nStrategies: ";
		for (const auto& strategy : playerStrategies) cout << *strategy << " "; // Dereference the pointer
		cout << "\nNumber of Games: " << numberOfGames;
		cout << "\nMax Number of Turns: " << maxNumberOfTurns << endl;

 
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
		game->update(userCommand);
		return true;
	}
	else if (userCommand == "validatemap" && currentSate == "maploaded")
	{
		cout << userCommand << " is valid in the state: " << currentSate;
		game->update(userCommand);
		return true;
	}
	else if ((userCommand == "addplayer" && currentSate == "mapvalidated") || (userCommand == "addplayer" && currentSate == "playersadded"))
	{
		cout << userCommand << " is valid in the state: " << currentSate;
		game->update(userCommand);
		return true;
	}
	else if (userCommand == "gamestart" && currentSate == "playersadded")
	{
		cout << userCommand << " is valid in the state: " << currentSate;
		game->update(userCommand);
		return true;
	}
	else if (userCommand == "replay" && currentSate == "win")
	{
		cout << userCommand << " is valid in the state: " << currentSate;
		game->update(userCommand);
		return true;
	}
	else if (userCommand == "quit" && currentSate == "win")
	{
		cout << userCommand << " is valid in the state: " << currentSate;
		game->update(userCommand);
		return true;
	}

	else if (userCommand == "tournament" && currentSate == "start") {
		Tournament* tournamentCmd = dynamic_cast<Tournament*>(command); //using dynamic casting here 
		vector<string*> mapFiles = tournamentCmd->getMapFiles(); 
        vector<string*> playerStrategies = tournamentCmd->getPlayerStrategies();
        int numberOfGames = tournamentCmd->getNumberOfGames();
        int maxNumberOfTurns = tournamentCmd->getMaxNumberOfTurns();

		
		if (mapFiles.size() < 1 || mapFiles.size() > 5) {
            cout << "Invalid number of maps." << endl;
            return false;
        }
        if (playerStrategies.size() < 2 || playerStrategies.size() > 4) {
            cout << "Invalid number of player strategies." << endl;
            return false;
        }
        if (numberOfGames < 1 || numberOfGames > 5) {
            cout << "Invalid number of games." << endl;
            return false;
        }
        if (maxNumberOfTurns < 10 || maxNumberOfTurns > 50) {
            cout << "Invalid number of turns." << endl;
            return false;
        }
        cout << userCommand << " is valid in the state: " << currentSate;
        game->update(userCommand); 
		return true;
    }


	else
	{
		if (this->getIndexCmdVector(userCommand) == -1)
		{
			cout << "Invalid command";
			return false;
		}
		else
		{
			cout << userCommand << " is not a vlalid command in this state";
			return false;
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

Tournament::Tournament()
{
}

Tournament::Tournament(std::vector<std::string*> m, std::vector<std::string*> p, int g, int t)
    : mapsFiles(m), listOfplayersStrategies(p), games(g), turns(t) {
}

vector<string*>& Tournament::getMapFiles() {
    return mapsFiles;
}

vector<string*>& Tournament::getPlayerStrategies() {
    return listOfplayersStrategies;
}

int Tournament::getNumberOfGames() const {
    return games;
}

int Tournament::getMaxNumberOfTurns() const {
    return turns;
}
