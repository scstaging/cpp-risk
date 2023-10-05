#include <iostream>
#include <typeinfo>
#include "GameEngine.h"

// Defines each update function to handle transitions using the command
// Control flow through available commands and handles accordingly
// getInstance returns a new single object of defined type
// Singleton pattern used to avoid excessive instantiation

// Concrete State Class Declerations
void Start::update(GameEngine* game, std::string command)
{
    if (command == "loadmap")
        game->setState(MapLoaded::getInstance());
}
GameState& Start::getInstance()
{
    static Start singleton;
    return singleton;
}

void MapLoaded::update(GameEngine* game, std::string command)
{
    if (command == "validatemap")
        game->setState(MapValidated::getInstance());
    else if (command == "loadmap")
        std::cout << "Not the state change command." << std::endl;
}
GameState& MapLoaded::getInstance()
{
    static MapLoaded singleton;
    return singleton;
}

void MapValidated::update(GameEngine* game, std::string command)
{
    if (command == "addplayer")
        game->setState(PlayersAdded::getInstance());
}
GameState& MapValidated::getInstance()
{
    static MapValidated singleton;
    return singleton;
}

void PlayersAdded::update(GameEngine* game, std::string command)
{
    if (command == "assigncountries")
        game->setState(AssignReinforcements::getInstance());
    else if (command == "addplayer")
        std::cout << "Not the state change command." << std::endl;
}
GameState& PlayersAdded::getInstance()
{
    static PlayersAdded singleton;
    return singleton;
}

void AssignReinforcements::update(GameEngine* game, std::string command)
{
    if (command == "issueorder")
        game->setState(IssueOrders::getInstance());
}
GameState& AssignReinforcements::getInstance()
{
    static AssignReinforcements singleton;
    return singleton;
}

void IssueOrders::update(GameEngine* game, std::string command)
{
    if (command == "endissueorders")
        game->setState(ExecuteOrders::getInstance());
    else if (command == "issueorder")
        std::cout << "Not the state change command." << std::endl;
}
GameState& IssueOrders::getInstance()
{
    static IssueOrders singleton;
    return singleton;
}

void ExecuteOrders::update(GameEngine* game, std::string command)
{
    if (command == "win")
        game->setState(Win::getInstance());
    else if (command == "endexecorders")
        game->setState(AssignReinforcements::getInstance());
    else if (command == "execorder")
        std::cout << "Not the state change command." << std::endl;
}
GameState& ExecuteOrders::getInstance()
{
    static ExecuteOrders singleton;
    return singleton;
}

void Win::update(GameEngine* game, std::string command)
{
    if (command == "end")
        std::exit(0);
    else if (command == "play")
        game->setState(Start::getInstance());
}
GameState& Win::getInstance()
{
    static Win singleton;
    return singleton;
}

// Game Engine Class Declerations

// Starts engine by setting currentState to beginning
GameEngine::GameEngine()
{
    // Returns reference becuase GameEngine stores current state as pointer
    currentState = &Start::getInstance();
}

// Handles transition exit and enter logic and sets new state
void GameEngine::setState(GameState& newState)
{
    // Execute code on exiting transition
    currentState->exit(this);
    // Change transition
    currentState = &newState;
    // Execute code on entering transition
    currentState->enter(this);
}

// Update function declared by each instance of GameState, and used here
void GameEngine::update(std::string command)
{
    // Game engine update applies unique state's update logic
    currentState->update(this, command);
}

/*
    References: 

    Hovhannisyan, A. (2023, August 14). Implementing a finite state machine in C++. Aleksandr Hovhannisyan. https://www.aleksandrhovhannisyan.com/blog/implementing-a-finite-state-machine-in-cpp/
        --> Heavily references in implementation of Finite State Machine for the game engine
*/