#pragma once

#include "testPlayerStrategies.h"

void createTestEnviornment(Map* map, vector<Player*> players)
{
    vector<Continent*> continents = map->getContinent();
    // Iterate through every continent
    for (int i = 0; i < continents.size(); i++)
    {
        // Iterate through every territory in a continent
        for (int j = 0; j < continents[i]->getContinentTerritories().size(); j++)
        {
            int randAssignment = rand() % 4;
            continents[i]->getContinentTerritories()[j]->setOwnerPlayer(players[randAssignment]);
        }
    }
}

void testPlayerStrategies()
{
    Maploader* maploader = new Maploader();
    Map* map = maploader->readFiles("./map1.map");

    cout << map->getContinent()[0]->getContinentTerritories().size() << endl;
    cout << map->getContinent()[2]->getContinentTerritories().size() << endl;
    cout << map->getContinent()[5]->getContinentTerritories().size() << endl;

    // Vector array of 4 different computer strategies
    std::vector<PlayerStrategy*> strats = {new AggressivePlayerStrategy(), new BenevolentPlayerStrategy(), new NeutralPlayerStrategy(), new CheaterPlayerStrategy()};

    // Instantiates 4 computer players
    Player* aggressive = new Player("aggressive", strats[0]);
    Player* benevolent = new Player("benevolent", strats[1]);
    Player* neutral = new Player("neutral", strats[2]);
    Player* cheater = new Player("cheater", strats[3]);

    vector<Player*> listOfPlayers = {aggressive, benevolent, neutral, cheater};

    createTestEnviornment(map, listOfPlayers);

    GameEngine* game = new GameEngine();
    Deck* deck = new Deck();

    cheater->issueOrder(cheater, deck, map, game);

    // Memory safe
    delete(aggressive);
    aggressive = nullptr;
    delete(benevolent);
    benevolent = nullptr;
    delete(neutral);
    neutral = nullptr;
    delete(cheater);
    cheater = nullptr;
}