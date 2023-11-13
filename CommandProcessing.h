#pragma once
#include <string>
#include <vector>
#include "GameEngine.h"
#include "LoggingObserver.h"

using namespace std;

// Command class - object containing the information the user has written
class Command : public Subject
{
public:
    enum class commandType
    {
        loadmap,
        validatemap,
        addplayer,
        gamestart,
        replay,
        quit
    };

    Command(string); // list of constructors and operator to create the command object
    Command(commandType, string);
    Command(const Command &command);
    Command &operator=(const Command &);
    void saveEffect(Command *);
    string getCommandStr();
    void setCommandStr();
    string getEffect();
    string getAddition();
    
    // Logging Observer
    string stringToLog();

    // stringToLog Implementation for ILoggable
    // string stringToLog();

    friend ostream &operator<<(ostream &, const Command &);

private:
    string commandStr;
    string effect{"Invalid Command"};

    // Additional string to add for commands such as loadmap and addplayer to get an output such as loadmap <map name>
    string addition{""};

    // Integer ID to idenfity the different types of commands. By default this is -1 for invalid commands
    int commandNumber{-1};
};

// CommandProcessor class - reads the console
class CommandProcessor : public Subject
{
public:
    CommandProcessor();
    CommandProcessor(const CommandProcessor &);
    CommandProcessor &operator=(const CommandProcessor &);
    ~CommandProcessor();
    virtual Command *readCommand();
    void getCommand(GameEngine *, CommandProcessor *);
    void saveCommand(Command *);
    void saveValidCommand(Command *);
    bool validate(Command *, GameEngine *);
    vector<Command *> getCommandList();
    vector<Command *> getValidCommandList();
    int getIndexCmdVector(string);
    bool getExitProgram();
    void setcmdProPause(bool);
    bool getcmdProPause();

    // Logging Observer Overrride
    std::string stringToLog();

    // stringToLog Implementation for ILoggable

    friend ostream &operator<<(ostream &, const vector<Command *> &);

private:

    // Vector of all commands written in the console
    vector<Command *> commandList;

    // Vector of all valid commands written in the console
    vector<Command *> validCommandList;

    // Boolean to see if the program should exit
    bool exitProgram = false;

    // Boolean to see if the commandProcessor should pause
    bool cmdProPause = false;

    // Vector of valid commands
    vector<string> commandVector = {"loadmap", "validatemap", "addplayer", "gamestart", "replay", "quit"};
};

// FileLineReader class - reads from a file
class FileLineReader
{
public:
    FileLineReader();
    FileLineReader(const FileLineReader &);
    FileLineReader &operator=(const FileLineReader &);
    void readLineFromFile(string);
    vector<string> getFileContent();

    friend ostream &operator<<(ostream &, const vector<string>);

private:
    vector<string> fileContent;
};

// FileCommandProcessorAdapter class - adapts the content read from a file for the CommandProcessor to understand
class FileCommandProcessorAdapter : public CommandProcessor
{
public:
    FileCommandProcessorAdapter(FileLineReader *);
    FileCommandProcessorAdapter(const FileCommandProcessorAdapter &);
    FileCommandProcessorAdapter &operator=(const FileCommandProcessorAdapter &);
    ~FileCommandProcessorAdapter();
    FileLineReader *getFileLineReader();
    Command *readCommand();

    friend ostream &operator<<(ostream &, const vector<string>);

private:
    FileLineReader *flr;

    // Index representing each line read by the file. Starts at -1 since the readCommand() method increases it by one every time it is called.
    int index{-1};

    // Vector of all commands read from the file
    vector<string> commands{};
};