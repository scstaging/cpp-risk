#pragma once
#include <vector>
#include <string>

class GameEngine;

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
        void enter(GameEngine* game) {}
        void update(GameEngine* game, std::string command);
        void exit(GameEngine* game) {}
        static GameState& getInstance();
        std::string getStateName()
        {
            return this->stateName;
        }
        std::string getChangeState()
        {
            return this->changeState;
        }

    private:
        Start() 
        { 
            this->stateName = "Start";
            this->transitions = { "loadmap" };
            this->changeState = "loadmap";
        }

        // Copy constructor
        Start(Start &other)
        {
            // Member copys
            this->stateName = other.stateName;
            this->transitions = other.transitions;
            this->changeState = other.changeState;
        }

        // Assignment Operator
        Start& operator=(const Start& other);

        // Stream Insertion Overload
        std::istream& operator >> (std::istream &in)
        {
            // Might be useful later

        }
        
};

class MapLoaded : public GameState
{
    public:
        void enter(GameEngine* game) {}
        void update(GameEngine* game, std::string command);
        void exit(GameEngine* game) {}
        static GameState& getInstance();
        std::string getStateName()
        {
            return this->stateName;
        }
        std::string getChangeState()
        {
            return this->changeState;
        }

    private:
        MapLoaded() 
        { 
            this->stateName = "Map Loaded"; 
            this->transitions = { "loadmap", "validatemap" };
            this->changeState = "validatemap";
        }
        
        // Copy constructor
        MapLoaded(MapLoaded &other)
        {
            // Member copys
            this->stateName = other.stateName;
            this->transitions = other.transitions;
            this->changeState = other.changeState;
        }

        // Assignment operator overload
        MapLoaded& operator=(const MapLoaded& other);

        // Stream Insertion Overload
        std::istream& operator >> (std::istream &in)
        {
            // Might be useful later

        }
};

class MapValidated : public GameState
{
    public:
        void enter(GameEngine* game) {}
        void update(GameEngine* game, std::string command);
        void exit(GameEngine* game) {}
        static GameState& getInstance();
        std::string getStateName()
        {
            return this->stateName;
        }
        std::string getChangeState()
        {
            return this->changeState;
        }

    private:
        MapValidated() 
        { 
            this->stateName = "Map Validated"; 
            this->transitions = { "addplayer" };
            this->changeState = "addplayer";
        }

         // Copy constructor
        MapValidated(MapValidated &other)
        {
            // Member copys
            this->stateName = other.stateName;
            this->transitions = other.transitions;
            this->changeState = other.changeState;
        }

        MapValidated& operator=(const MapValidated& other);

        // Stream Insertion Overload
        std::istream& operator >> (std::istream &in)
        {
            // Might be useful later

        }
};

class PlayersAdded : public GameState
{
    public:
        void enter(GameEngine* game) {}
        void update(GameEngine* game, std::string command);
        void exit(GameEngine* game) {}
        static GameState& getInstance();
        std::string getStateName()
        {
            return this->stateName;
        }
        std::string getChangeState()
        {
            return this->changeState;
        }

    private:
        PlayersAdded() 
        { 
            this->stateName = "Players Added"; 
            this->transitions = { "addplayer", "assigncountries" };
            this->changeState = "assigncountries";
        }
        
        // Copy constructor
        PlayersAdded(PlayersAdded &other)
        {
            // Member copys
            this->stateName = other.stateName;
            this->transitions = other.transitions;
            this->changeState = other.changeState;
        }
        
        PlayersAdded& operator=(const PlayersAdded& other);

        // Stream Insertion Overload
        std::istream& operator >> (std::istream &in)
        {
            // Might be useful later

        }
};

class AssignReinforcements : public GameState
{
    public:
        void enter(GameEngine* game) {}
        void update(GameEngine* game, std::string command);
        void exit(GameEngine* game) {}
        static GameState& getInstance();
        std::string getStateName()
        {
            return this->stateName;
        }
        std::string getChangeState()
        {
            return this->changeState;
        }

    private:
        AssignReinforcements() 
        { 
            this->stateName = "Assign Reinforcements"; 
            this->transitions = { "issueorder" };
            this->changeState = "issueorder";
        }
        
        // Copy constructor
        AssignReinforcements(AssignReinforcements &other)
        {
            // Member copys
            this->stateName = other.stateName;
            this->transitions = other.transitions;
            this->changeState = other.changeState;
        }

        AssignReinforcements& operator=(const AssignReinforcements& other);

        // Stream Insertion Overload
        std::istream& operator >> (std::istream &in)
        {
            // Might be useful later

        }
};

class IssueOrders : public GameState
{
    public:
        void enter(GameEngine* game) {}
        void update(GameEngine* game, std::string command);
        void exit(GameEngine* game) {}
        static GameState& getInstance();
        std::string getStateName()
        {
            return this->stateName;
        }
        std::string getChangeState()
        {
            return this->changeState;
        }

    private:
        IssueOrders() 
        { 
            this->stateName = "Issue Orders";
            this->transitions = { "issueorder", "endissueorders" };
            this->changeState = "endissueorders";
        }

        // Copy constructor
        IssueOrders(IssueOrders &other)
        {
            // Member copys
            this->stateName = other.stateName;
            this->transitions = other.transitions;
            this->changeState = other.changeState;
        }

        IssueOrders& operator=(const IssueOrders& other);

        // Stream Insertion Overload
        std::istream& operator >> (std::istream &in)
        {
            // Might be useful later

        }
};

class ExecuteOrders : public GameState
{
    public:
        void enter(GameEngine* game) {}
        void update(GameEngine* game, std::string command);
        void exit(GameEngine* game) {}
        static GameState& getInstance();
        std::string getStateName()
        {
            return this->stateName;
        }
        std::string getChangeState()
        {
            return this->changeState;
        }

    private:
        ExecuteOrders() 
        { 
            this->stateName = "Execute Orders";
            this->transitions = { "execorder", "endexecorders", "win" };
            this->changeState = "win";
        }
        
        // Copy constructor
        ExecuteOrders(ExecuteOrders &other)
        {
            // Member copys
            this->stateName = other.stateName;
            this->transitions = other.transitions;
            this->changeState = other.changeState;
        }

        ExecuteOrders& operator=(const ExecuteOrders& other);

        // Stream Insertion Overload
        std::istream& operator >> (std::istream &in)
        {
            // Might be useful later

        }
};

class Win : public GameState
{
    public:
        void enter(GameEngine* game) {}
        void update(GameEngine* game, std::string command);
        void exit(GameEngine* game) {}
        static GameState& getInstance();
        std::string getStateName()
        {
            return this->stateName;
        }
        std::string getChangeState()
        {
            return this->changeState;
        }

    private:
        Win() 
        { 
            this->stateName = "Win";
            this->transitions = { "play", "end" }; 
            this->changeState = "end";
        }

        // Copy constructor
        Win(Win &other)
        {
            // Member copys
            this->stateName = other.stateName;
            this->transitions = other.transitions;
            this->changeState = other.changeState;
        }

        Win& operator=(const Win& other);

        // Stream Insertion Overload
        std::istream& operator >> (std::istream &in)
        {
            // Might be useful later

        }
};

// Game Engine Class
class GameEngine
{
    private:
        // Stores pointer to current state
        GameState* currentState;
    public:
        GameEngine();
        // Returns current state
        inline std::string getCurrentState() const { return currentState->getStateName(); }
        
        // Iterates through transitions
        bool validateTransition(std::string x) {
            // O(n) but x is almost exclusively < 3
            for (int i = 0; i < currentState->transitions.size(); i++) {
                // Checks if command is in array of transitions
                if (x == currentState->transitions[i])
                    return true;
            }
            // Command is not in array of transitions
            return false;
        }

        // Checks if command is the transition command
        bool validateChangeState(std::string x) { return x == currentState->getChangeState(); }
        // Updates state
        void update(std::string command);
        // Each transition applies it's own logic
        void setState(GameState& newState);
};

/*
    References: 

    Hovhannisyan, A. (2023, August 14). Implementing a finite state machine in C++. Aleksandr Hovhannisyan. https://www.aleksandrhovhannisyan.com/blog/implementing-a-finite-state-machine-in-cpp/
        --> Heavily references in implementation of Finite State Machine for the game engine
*/