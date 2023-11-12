#include <iostream>
using namespace std;
#include <typeinfo>
#include <algorithm>
#include <map>
#include "GameEngine.h"
#include "Player.h"
#include "Map.h"
#include "Cards.h"
#include "Orders.h"

// Defines each update function to handle transitions using the command
// Control flow through available commands and handles accordingly
// getInstance returns a new single object of defined type
// Singleton pattern used to avoid excessive instantiation

// Concrete State Class Declerations

const int GameEngine::MINIMUM_NUMBER_OF_REINFORCEMENTS = 3;

// Default constructor
Start::Start() 
{ 
    this->stateName = "Start";
    this->transitions = { "loadmap" };
    this->changeState = "loadmap";
}
// Copy constructor
Start::Start(Start &other)
{
    // Member copys
    this->stateName = other.stateName;
    this->transitions = other.transitions;
    this->changeState = other.changeState;
}
void Start::enter(GameEngine *game)
{
    // On entering a transition
}
void Start::exit(GameEngine *game)
{
    // On leaving a transition
}
std::string Start::getStateName()
{
    return this->stateName;
}
std::string Start::getChangeState()
{
    return this->changeState;
}
void Start::update(GameEngine *game, std::string command)
{
    if (command == "loadmap")
        game->setState(MapLoaded::getInstance());
}
GameState &Start::getInstance()
{
    static Start singleton;
    return singleton;
}

// Default constructor
MapLoaded::MapLoaded() 
{ 
    this->stateName = "Map Loaded"; 
    this->transitions = { "loadmap", "validatemap" };
    this->changeState = "validatemap";
}
// Copy constructor
MapLoaded::MapLoaded(MapLoaded &other)
{
    // Member copys
    this->stateName = other.stateName;
    this->transitions = other.transitions;
    this->changeState = other.changeState;
}
void MapLoaded::enter(GameEngine *game)
{
    // On entering a transition
}
void MapLoaded::exit(GameEngine *game)
{
    // On leaving a transition
}
std::string MapLoaded::getStateName()
{
    return this->stateName;
}
std::string MapLoaded::getChangeState()
{
    return this->changeState;
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

// Default constructor
MapValidated::MapValidated() 
{ 
    this->stateName = "Map Validated"; 
    this->transitions = { "addplayer" };
    this->changeState = "addplayer";
}

    // Copy constructor
MapValidated::MapValidated(MapValidated &other)
{
    // Member copys
    this->stateName = other.stateName;
    this->transitions = other.transitions;
    this->changeState = other.changeState;
}
void MapValidated::enter(GameEngine *game)
{
    // On entering a transition
}
void MapValidated::exit(GameEngine *game)
{
    // On leaving a transition
}
std::string MapValidated::getStateName()
{
    return this->stateName;
}
std::string MapValidated::getChangeState()
{
    return this->changeState;
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

// Default constructor
PlayersAdded::PlayersAdded() 
{ 
    this->stateName = "Players Added"; 
    this->transitions = { "addplayer", "assigncountries" };
    this->changeState = "assigncountries";
}  
 // Copy constructor
PlayersAdded::PlayersAdded(PlayersAdded &other)
{
    // Member copys
    this->stateName = other.stateName;
    this->transitions = other.transitions;
    this->changeState = other.changeState;
}
void PlayersAdded::enter(GameEngine *game)
{
    // On entering a transition
}
void PlayersAdded::exit(GameEngine *game)
{
    // On leaving a transition
}
std::string PlayersAdded::getStateName()
{
    return this->stateName;
}
std::string PlayersAdded::getChangeState()
{
    return this->changeState;
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
// Reinforcement Phase

// Default constructor
AssignReinforcements::AssignReinforcements() 
{ 
    this->stateName = "Assign Reinforcements"; 
    this->transitions = { "issueorder" };
    this->changeState = "issueorder";
}
// Copy constructor
AssignReinforcements::AssignReinforcements(AssignReinforcements &other)
{
    // Member copys
    this->stateName = other.stateName;
    this->transitions = other.transitions;
    this->changeState = other.changeState;
}
void AssignReinforcements::enter(GameEngine *game)
{
    // On entering a transition
}
void AssignReinforcements::exit(GameEngine *game)
{
    // On leaving a transition
}
std::string AssignReinforcements::getStateName()
{
    return this->stateName;
}
std::string AssignReinforcements::getChangeState()
{
    return this->changeState;
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

// Issuing Order Phase

// Default constructor
IssueOrders::IssueOrders() 
{ 
    this->stateName = "Issue Orders";
    this->transitions = { "issueorder", "endissueorders" };
    this->changeState = "endissueorders";
}
// Copy constructor
IssueOrders::IssueOrders(IssueOrders &other)
{
    // Member copys
    this->stateName = other.stateName;
    this->transitions = other.transitions;
    this->changeState = other.changeState;
}
void IssueOrders::enter(GameEngine *game)
{
    // On entering a transition
}
void IssueOrders::exit(GameEngine *game)
{
    // On leaving a transition
}
std::string IssueOrders::getStateName()
{
    return this->stateName;
}
std::string IssueOrders::getChangeState()
{
    return this->changeState;
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

// Execute Orders Phase


// Default constructor
ExecuteOrders::ExecuteOrders() 
{ 
    this->stateName = "Execute Orders";
    this->transitions = { "execorder", "endexecorders", "win" };
    this->changeState = "win";
}
// Copy constructor
ExecuteOrders::ExecuteOrders(ExecuteOrders &other)
{
    // Member copys
    this->stateName = other.stateName;
    this->transitions = other.transitions;
    this->changeState = other.changeState;
}
void ExecuteOrders::enter(GameEngine *game)
{
    // On entering a transition
}
void ExecuteOrders::exit(GameEngine *game)
{
    // On leaving a transition
}
std::string ExecuteOrders::getStateName()
{
    return this->stateName;
}
std::string ExecuteOrders::getChangeState()
{
    return this->changeState;
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

// Default constructor
Win::Win() 
{ 
    this->stateName = "Win";
    this->transitions = { "play", "end" }; 
    this->changeState = "end";
}
// Copy constructor
Win::Win(Win &other)
{
    // Member copys
    this->stateName = other.stateName;
    this->transitions = other.transitions;
    this->changeState = other.changeState;
}
void Win::enter(GameEngine *game)
{
    // On entering a transition
}
void Win::exit(GameEngine *game)
{
    // On leaving a transition
}
std::string Win::getStateName()
{
    return this->stateName;
}
std::string Win::getChangeState()
{
    return this->changeState;
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

// Copy constructor
GameEngine::GameEngine(GameEngine &other)
{
    this->currentState = other.currentState;
}

// Returns current state
std::string GameEngine::getCurrentState() { return currentState->getStateName(); }

// Iterates through transitions
bool GameEngine::validateTransition(std::string x) {
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
bool GameEngine::validateChangeState(std::string x) { return x == currentState->getChangeState(); }

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

list<Player*> GameEngine::getPlayers(){
    return listOfPlayers;
}

void GameEngine::mainGameLoop(){
    bool gameOver = false;
    std::string* winningPlayer;

    while(!gameOver){
        // Reinforcements Phase
        reinforcementsPhase();
        // Issue Orders Phase
        issueOrdersPhase();
        // Execute Orders Phase
        executeOrdersPhase();

        //Checks to see if anyone has lost all their territories
        auto it = listOfPlayers.begin();
        while (it != listOfPlayers.end()) {
            auto currentPlayer = it++;
            if ((*currentPlayer)->getTerritories().empty()) {
                cout << (*currentPlayer)->getPlayerName() << "has lost all their territories!" << endl; 
                listOfPlayers.erase(currentPlayer);
            }
        }

        //Checks to see if anyone has conquered all territories
        for (Player* player : listOfPlayers){
            if(player->getTerritories().size() == map->getTerritory().size()){
                gameOver = true;  
                winningPlayer = player->getPlayerName();
            } 
        }
    };

    cout<< "The winner is: " << winningPlayer << "!" << endl;


}

void GameEngine::reinforcementsPhase(){
    for(Player* player : listOfPlayers){
        int reinforcement = 0; 
        int territoriesOwned = player->getTerritories().size(); 

        //Integer division so result is rounded down
        reinforcement += territoriesOwned / 3;

        //Updates list of continents that player owns territories in. 
        for(Territory* t : player->getTerritories()){
            Continent* continent = t->getContinent();
            vector<Continent*> playerContinents = player->getContinents(); 

            auto it = find_if(playerContinents.begin(), playerContinents.end(), 
                       [continent](const Continent* c) { return c == continent; });

            if(it == playerContinents.end()){
                playerContinents.push_back(continent);
            }
        }

        //Checks to see if player owns all territories in any continent. Applies control bonus if this is the case.
        for(Continent* c : player->getContinents()){
            int ownedTerritories = 0; 
            const std::vector<Territory*>& continentTerritories = c->getContinentTerritories();
            vector<Territory*> playerTerritories = player->getTerritories();

            for(Territory* t : continentTerritories){
                auto it = find_if(playerTerritories.begin(), playerTerritories.end(),
                       [t](const Territory* territory) { return territory == t; });
                if(it != playerTerritories.end()){
                    ownedTerritories++;
                }
            }

            if(ownedTerritories == continentTerritories.size()){
                reinforcement += c->getControlBonus(); 
            }
        }

        //Gives player minimum number of reinforcements if current count is below. 
        if(reinforcement < MINIMUM_NUMBER_OF_REINFORCEMENTS){
            reinforcement = MINIMUM_NUMBER_OF_REINFORCEMENTS;
        }

        //Adds reinforcements to the player's reinforcement pool. 
        player->incrementReinforcementPool(reinforcement);
    }
}

void GameEngine::issueOrdersPhase(){

    std::map<string*, bool> playerStatus;

    // Setting all the values of playerStatus to true
    for (Player* player : listOfPlayers) {
        playerStatus[player->getPlayerName()] = true;
    }

    //Will keep count of the players that have not ended their turn
    int playersThatCanGo = listOfPlayers.size();
    
    //Will go through list of players until all players have ended their turn
    while(playersThatCanGo > 0){
        for(Player* player : listOfPlayers){
            if(playerStatus[player->getPlayerName()]){
                //issueOrder function will return "true" if turn is not ended, and "false" if it is
                playerStatus[player->getPlayerName()] = player->issueOrder(this->deck, this->map);
                
                //if issueOrder function returns "false", means player has ended their turn. Decrements # of players that can go
                if(!playerStatus[player->getPlayerName()]){
                    playersThatCanGo--;
                }
            }
        }
    }
}

void GameEngine::executeOrdersPhase(){
    int numFinishedPlayers = 0; 

    std::map<string*, bool> playerOrderStatus;

    for(Player* player : listOfPlayers){
        playerOrderStatus[player->getPlayerName()] = true;
    }

    while(numFinishedPlayers != listOfPlayers.size()){
        for(Player* player : listOfPlayers){

            if(playerOrderStatus[player->getPlayerName()]){

                list<Order*> playerOrderList = player->getOrdersList()->getOrders();

                if(playerOrderList.empty()){
                    numFinishedPlayers++;
                    playerOrderStatus[player->getPlayerName()] = false;
                }
                else{
                    playerOrderList.front()->execute();
                }
            } 
        }
    }
}

int main(){

    //Creating a test player
    Player* testPlayer = new Player("Testington");

    //Creating a test continent
    Continent* testContinent = new Continent;

    //Creating test territories
    Territory* testTerritory1 = new Territory("Territory1", testContinent, 5, 5);
    Territory* testTerritory2 = new Territory("Territory2", testContinent, 5, 5);
    Territory* testTerritory3 = new Territory("Territory3", testContinent, 5, 5);

    //Creating a vector that contains the player's territories
    vector<Territory*> playerTerritories = testPlayer->getTerritories();

    //Adding test territories to player
    playerTerritories.push_back(testTerritory1);
    playerTerritories.push_back(testTerritory2);
    playerTerritories.push_back(testTerritory3);

    //Creating test engine
    GameEngine* testEngine = new GameEngine();

    //Creating a list that contains the game engine's players
    list<Player*> listOfPlayers = testEngine->getPlayers();

    //Adding test player to game engine
    listOfPlayers.push_back(testPlayer);

    testEngine->reinforcementsPhase();

    return 0;
}

/*
    References: 

    Hovhannisyan, A. (2023, August 14). Implementing a finite state machine in C++. Aleksandr Hovhannisyan. https://www.aleksandrhovhannisyan.com/blog/implementing-a-finite-state-machine-in-cpp/
        --> Heavily references in implementation of Finite State Machine for the game engine
*/