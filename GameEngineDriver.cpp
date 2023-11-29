#include <iostream>
#include "GameEngine.h"

// Free Function testGameStates()
void testGameStates() {

// Instantiates game engine
GameEngine* engine = new GameEngine();

    // while true, allows for breaking only when necessary
    while (true)
    {

        // Display relevant information on each new iteration
        std::cout << "\nCurrent State: " << engine->getCurrentState() << std::endl;
        std::cout << "Enter Command: ";
        
        // Takes command as input
        std::string x;
        std::cin >> x;

        // Checks if input exists for current state
        if (engine->validateTransition(x)) 
        {
            // Evaluates where to transition to
            engine->update(x);
        }
        
        // Input does not exist
        else
        {
            // Display error message for incorrect input
            std::cout << "Input is not recognized" << std::endl;
        }
    }

    // Frees up memory
    delete engine;
    engine = NULL;
}

int main() {
    testGameStates();

//     return 0;
// };

int testMainGameLoop(){

    //Creating a test player
    Player* testPlayer = new Player("Testington");
    Player* testPlayer2 = new Player("Testington2");
    Player* testPlayer3 = new Player("Testington3");

    //Creating a test continent
    Continent* testContinent = new Continent;

    //Creating test territories
    Territory* testTerritory1 = new Territory("Territory1", testContinent, 5, 5);
    Territory* testTerritory2 = new Territory("Territory2", testContinent, 5, 5);
    Territory* testTerritory3 = new Territory("Territory3", testContinent, 5, 5);
    Territory* testTerritory4 = new Territory("Territory4", testContinent, 5, 5);
    Territory* testTerritory5 = new Territory("Territory5", testContinent, 5, 5);
    Territory* testTerritory6 = new Territory("Territory6", testContinent, 5, 5);
    Territory* testTerritory7 = new Territory("Territory7", testContinent, 5, 5);
    Territory* testTerritory8 = new Territory("Territory8", testContinent, 5, 5);
    Territory* testTerritory9 = new Territory("Territory9", testContinent, 5, 5);
    Territory* testTerritory10 = new Territory("Territory10", testContinent, 5, 5);

    //Creating a vector that contains the player's territories
    vector<Territory*> playerTerritories = testPlayer->getTerritories();
    vector<Territory*> player2Territories = testPlayer2->getTerritories();

    //Adding test territories to player so that they have enough to receive more than minimum requirement
    playerTerritories.push_back(testTerritory1);
    playerTerritories.push_back(testTerritory2);
    playerTerritories.push_back(testTerritory3);
    playerTerritories.push_back(testTerritory4);
    playerTerritories.push_back(testTerritory5);
    playerTerritories.push_back(testTerritory6);
    playerTerritories.push_back(testTerritory7);
    playerTerritories.push_back(testTerritory8);
    playerTerritories.push_back(testTerritory9);

    //Adding test territory to player 2 so that they receive less than minimum requirement
    player2Territories.push_back(testTerritory10);

    //Note: testPlayer3 should be removed since they carry no territories

    //Creating test engine
    GameEngine* testEngine = new GameEngine();

    //Creating a list that contains the game engine's players
    list<Player*> listOfPlayers = testEngine->getPlayers();

    //Adding test player to game engine
    listOfPlayers.push_back(testPlayer);
    listOfPlayers.push_back(testPlayer2);
    listOfPlayers.push_back(testPlayer3);

    testEngine->mainGameLoop();

    return 0;
}

