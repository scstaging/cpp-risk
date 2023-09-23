#pragma once
#include <vector>
#include <string>

class GameEngine;

// State Template Class
class GameState
{
    public:
        virtual void enter(GameEngine* game) = 0;
        virtual void update(GameEngine* game, std::string command) = 0;
        virtual void exit(GameEngine* game) = 0;
        std::string stateName = "";
        std::string changeState = "";
        std::vector<std::string> transitions;
        virtual ~GameState() {}
};

// Concrete State Classes
class Start : public GameState
{
    public:
        void enter(GameEngine* game) {}
        void update(GameEngine* game, std::string command);
        void exit(GameEngine* game) {}
        static GameState& getInstance();

    private:
        Start() 
        { 
            this->stateName = "Start";
            this->transitions = { "loadmap" };
            this->changeState = "loadmap";
        }
        Start(const Start& other);
        Start& operator=(const Start& other);
};

class MapLoaded : public GameState
{
    public:
        void enter(GameEngine* game) {}
        void update(GameEngine* game, std::string command);
        void exit(GameEngine* game) {}
        static GameState& getInstance();

    private:
        MapLoaded() 
        { 
            this->stateName = "Map Loaded"; 
            this->transitions = { "loadmap", "validatemap" };
            this->changeState = "validatemap";
        }
        MapLoaded(const MapLoaded& other);
        MapLoaded& operator=(const MapLoaded& other);
};

class MapValidated : public GameState
{
    public:
        void enter(GameEngine* game) {}
        void update(GameEngine* game, std::string command);
        void exit(GameEngine* game) {}
        static GameState& getInstance();

    private:
        MapValidated() 
        { 
            this->stateName = "Map Validated"; 
            this->transitions = { "addplayer" };
            this->changeState = "addplayer";
        }
        MapValidated(const MapValidated& other);
        MapValidated& operator=(const MapValidated& other);
};

class PlayersAdded : public GameState
{
    public:
        void enter(GameEngine* game) {}
        void update(GameEngine* game, std::string command);
        void exit(GameEngine* game) {}
        static GameState& getInstance();

    private:
        PlayersAdded() 
        { 
            this->stateName = "Players Added"; 
            this->transitions = { "addplayer", "assigncountries" };
            this->changeState = "assigncountries";
        }
        PlayersAdded(const PlayersAdded& other);
        PlayersAdded& operator=(const PlayersAdded& other);
};

class AssignReinforcements : public GameState
{
    public:
        void enter(GameEngine* game) {}
        void update(GameEngine* game, std::string command);
        void exit(GameEngine* game) {}
        static GameState& getInstance();

    private:
        AssignReinforcements() 
        { 
            this->stateName = "Assign Reinforcements"; 
            this->transitions = { "issueorder" };
            this->changeState = "issueorder";
        }
        AssignReinforcements(const AssignReinforcements& other);
        AssignReinforcements& operator=(const AssignReinforcements& other);
};

class IssueOrders : public GameState
{
    public:
        void enter(GameEngine* game) {}
        void update(GameEngine* game, std::string command);
        void exit(GameEngine* game) {}
        static GameState& getInstance();

    private:
        IssueOrders() 
        { 
            this->stateName = "Issue Orders";
            this->transitions = { "issueorder", "endissueorders" };
            this->changeState = "endissueorders";
        }
        IssueOrders(const IssueOrders& other);
        IssueOrders& operator=(const IssueOrders& other);
};

class ExecuteOrders : public GameState
{
    public:
        void enter(GameEngine* game) {}
        void update(GameEngine* game, std::string command);
        void exit(GameEngine* game) {}
        static GameState& getInstance();

    private:
        ExecuteOrders() 
        { 
            this->stateName = "Execute Orders";
            this->transitions = { "execorder", "endexecorders", "win" };
            this->changeState = "win";
        }
        ExecuteOrders(const ExecuteOrders& other);
        ExecuteOrders& operator=(const ExecuteOrders& other);
};

class Win : public GameState
{
    public:
        void enter(GameEngine* game) {}
        void update(GameEngine* game, std::string command);
        void exit(GameEngine* game) {}
        static GameState& getInstance();

    private:
        Win() 
        { 
            this->stateName = "Win";
            this->transitions = { "play", "end" }; 
            this->changeState = "end";
        }
        Win(const Win& other);
        Win& operator=(const Win& other);
};

// Game Engine Class
class GameEngine
{
    private:
        GameState* currentState;
    public:
        GameEngine();
        inline std::string getCurrentState() const { return currentState->stateName; }
        bool validateTransition(std::string x) {
            for (int i = 0; i < currentState->transitions.size(); i++) {
                if (x == currentState->transitions[i])
                    return true;
            }
            return false;
        }
        bool validateChangeState(std::string x) { return x == currentState->changeState; }
        void update(std::string command);
        void setState(GameState& newState);
};

/*
    References: 

    Hovhannisyan, A. (2023, August 14). Implementing a finite state machine in C++. Aleksandr Hovhannisyan. https://www.aleksandrhovhannisyan.com/blog/implementing-a-finite-state-machine-in-cpp/
        --> Heavily references in implementation of Finite State Machine for the game engine
*/