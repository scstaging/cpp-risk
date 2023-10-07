#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Continent
{
private:
    string nameOfContinent;

public:
    Continent();
    Continent(string name);
    string getNameOfContinent();
};

class Territory
{
private:
    vector<Territory *> adjacentTerritory;
    string nameOfTerritory;
    int x;
    int y;
    Continent *continent;
    // Player p1;
    // int numOfArmies
    // those attributes will be included in the next assignments since there are no obvious use of them.

public:
    Territory();
    Territory(string name, Continent *theContinent, int z, int w);
    vector<Territory *> getAdjacentTerritory();
    string getNameOfTerritory();
    Continent* getContinent();
    string getTerritoryName();
    void pushATerritoryToAdj(Territory* T);
};

class Map
{
private:
    vector<Territory *> theTerritories;
    vector<Continent *> theContinents;
    int forTrying;
    void depthFirstSearch(vector<string> &v1, Territory *T1);
    bool isConnectedTerritory();
    bool isConnectedContinent();
    void dfs_continent(vector<string> &visitedTerritoriesNames, Territory *currentTerritory, Continent *currentContinent);
    vector<Territory *> getTerritoryByContinent(Continent* C);

public:
    Map();
    Map(vector<Territory *> theTerritories1, vector<Continent *> theContinents1);
    void pushContinent(Continent *C);
    vector<Continent *> getContinent();
    void pushTerritory(Territory *T);
    vector<Territory *> getTerritory();
    void validate();
};

class Maploader
{

public:
    Map *readFiles(string filePath);
    Territory *getTerritoryByName(vector<Territory *> territories, string name);

    Continent *getContinentByName(vector<Continent *> continents, string name);
};