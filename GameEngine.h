#pragma once
#include <vector>
#include <string>
#include "Player.h"
#include "LoggingObserver.h"
#include <set>
#include <utility>

class GameEngine;
class Player;
class Map;
class Territory;

// State Template Class
class GameState
{
    public:
        // Code executed on entering transition
        virtual void enter(GameEngine* game) = 0;
        // Code executed on updating transition
        virtual void update(GameEngine* game, std::string command) = 0;
        // Code executed on leaving transition
        virtual void exit(GameEngine* game) = 0;
        // Returns state name
        virtual std::string getStateName() = 0;
        // Returns name of forward transition
        virtual std::string getChangeState() = 0;

        // Holds all possible transition values
        std::vector<std::string> transitions;

        // Deconstructor
        virtual ~GameState() {}

    protected:
        // Holds the state name
        std::string stateName = "";
        // Holds the transition name
        std::string changeState = "";
};

// Concrete State Classes
class Start : public GameState
{
    public:
        void enter(GameEngine* game);
        void update(GameEngine* game, std::string command);
        void exit(GameEngine* game);
        static GameState& getInstance();
        std::string getStateName();
        std::string getChangeState();

    private:
        Start();

        // Copy constructor
        Start(Start &other);

        // Assignment Operator
        Start& operator=(const Start& other);

        // Stream Insertion Overload
        std::istream& operator >> (std::istream &in);
};

class MapLoaded : public GameState
{
    public:
        void enter(GameEngine* game);
        void update(GameEngine* game, std::string command);
        void exit(GameEngine* game);
        static GameState& getInstance();
        std::string getStateName();
        std::string getChangeState();

    private:
        MapLoaded();
        
        // Copy constructor
        MapLoaded(MapLoaded &other);

        // Assignment operator overload
        MapLoaded& operator=(const MapLoaded& other);

        // Stream Insertion Overload
        std::istream& operator >> (std::istream &in);
};

class MapValidated : public GameState
{
    public:
        void enter(GameEngine* game);
        void update(GameEngine* game, std::string command);
        void exit(GameEngine* game);
        static GameState& getInstance();
        std::string getStateName();
        std::string getChangeState();

    private:
        MapValidated();

         // Copy constructor
        MapValidated(MapValidated &other);

        MapValidated& operator=(const MapValidated& other);

        // Stream Insertion Overload
        std::istream& operator >> (std::istream &in);
};

class PlayersAdded : public GameState
{
    public:
        void enter(GameEngine* game);
        void update(GameEngine* game, std::string command);
        void exit(GameEngine* game);
        static GameState& getInstance();
        std::string getStateName();
        std::string getChangeState();

    private:
        PlayersAdded();
        
        // Copy constructor
        PlayersAdded(PlayersAdded &other);
        
        PlayersAdded& operator=(const PlayersAdded& other);

        // Stream Insertion Overload
        std::istream& operator >> (std::istream &in);
};

class AssignReinforcements : public GameState
{
    public:
        void enter(GameEngine* game);
        void update(GameEngine* game, std::string command);
        void exit(GameEngine* game);
        static GameState& getInstance();
        std::string getStateName();
        std::string getChangeState();

    private:
        AssignReinforcements();
        
        // Copy constructor
        AssignReinforcements(AssignReinforcements &other);

        AssignReinforcements& operator=(const AssignReinforcements& other);

        // Stream Insertion Overload
        std::istream& operator >> (std::istream &in);
};

class IssueOrders : public GameState
{
    public:
        void enter(GameEngine* game);
        void update(GameEngine* game, std::string command);
        void exit(GameEngine* game);
        static GameState& getInstance();
        std::string getStateName();
        std::string getChangeState();

    private:
        IssueOrders();

        // Copy constructor
        IssueOrders(IssueOrders &other);

        IssueOrders& operator=(const IssueOrders& other);

        // Stream Insertion Overload
        std::istream& operator >> (std::istream &in);
};

class ExecuteOrders : public GameState
{
    public:
        void enter(GameEngine* game);
        void update(GameEngine* game, std::string command);
        void exit(GameEngine* game);
        static GameState& getInstance();
        std::string getStateName();
        std::string getChangeState();

    private:
        ExecuteOrders();
        
        // Copy constructor
        ExecuteOrders(ExecuteOrders &other);

        ExecuteOrders& operator=(const ExecuteOrders& other);

        // Stream Insertion Overload
        std::istream& operator >> (std::istream &in);
};

class Win : public GameState
{
    public:
        void enter(GameEngine* game);
        void update(GameEngine* game, std::string command);
        void exit(GameEngine* game);
        static GameState& getInstance();
        std::string getStateName();
        std::string getChangeState();

    private:
        Win();

        // Copy constructor
        Win(Win &other);

        Win& operator=(const Win& other);

        // Stream Insertion Overload
        std::istream& operator >> (std::istream &in);
};

// Game Engine Class
class GameEngine : public Subject
{
    private:
        // Stores pointer to current state
        GameState* currentState;
        list<Player*> listOfPlayers;
        Map* map;
        Deck* deck;
        std::set<std::pair<Player *, Player *>> activeNegotiations;


    public:

        static const int MINIMUM_NUMBER_OF_REINFORCEMENTS; 

        // Default constructor
        GameEngine();
        // Copy constructor
        GameEngine(GameEngine &other);
        // Assignment operator
        GameEngine& operator=(const GameEngine& other);
        // Stream Insertion Overload
        std::istream& operator >> (std::istream &in);

        // Logging Observer Overrride
        std::string stringToLog();

        // Returns current state
        std::string getCurrentState();
        
        // Iterates through transitions
        bool validateTransition(std::string x);

        // Checks if command is the transition command
        bool validateChangeState(std::string x);

        // Updates state
        void update(std::string command);

        // Each transition applies it's own logic
        void setState(GameState& newState);

        // Returns list of players
        list<Player*> getPlayers();

        void gameStart();

        // Triggers the startup phase of the game
        void startupPhase();

        // Triggers the main game loops 
        void mainGameLoop();

        // Triggers the reinforcement phase in the main game loop
        void reinforcementsPhase();

        // Triggers the issue orders phase in the main game loop
        void issueOrdersPhase();

        // Triggers the execute orders phase in the main game loop
        void executeOrdersPhase();

        // features for the order execution to verify if players negociated
        void addNegotiation(Player *player1, Player *player2);
        void clearNegotiations();
        bool isUnderNegotiation(Player *player1, Player *player2);
        
        // determine the owner of a territory
        Player* getOwnerOfTerritory(Territory* territory);
};

/*
    References: 

    Hovhannisyan, A. (2023, August 14). Implementing a finite state machine in C++. Aleksandr Hovhannisyan. https://www.aleksandrhovhannisyan.com/blog/implementing-a-finite-state-machine-in-cpp/
        --> Heavily references in implementation of Finite State Machine for the game engine
*/
