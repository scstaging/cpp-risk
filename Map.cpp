#include "Map.h"
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include <map>

using namespace std;

Map *Maploader::readFiles(string filePath)
{
    Map *theMap = new Map();
    string nameOfContinent;
    string nameOfTerritory;
    char tDelimiter = ',';
    string cDelimiter = "=";
    string line;
    string token;
    vector<string> ss;
    int found;
    ifstream reader(filePath);
    while (!reader.eof())
    {

        getline(reader, line);
        if (line == "[Continents]")
        {
            cout << "I reached continent" << endl;
            while (getline(reader, line))
            {
                if (line.length() == 0){
                    break;}
                found = line.find(cDelimiter);
                nameOfContinent = line.substr(0, found);
                Continent *ptrContinent =  new Continent(nameOfContinent); //Include read for control bonus
                theMap->pushContinent(ptrContinent);
            }
            // vector <Continent*> xx = theMap->getContinent();
            // for (auto i = 0; i<xx.size();i = i+1){
            //   cout<< xx[i]->getNameOfContinent() <<endl;
            // }
        }
      
        if (line == "[Territories]")
        {
            cout << "I reached Territories" << endl;
            while (getline(reader, line))
            {
                if (line.empty())
                {
                    break;
                }
                stringstream s(line);
                while (getline(s, token, tDelimiter))
                {
                    ss.push_back(token);
                }
                nameOfTerritory = ss[0];
                int x = stoi(ss[1]);
                int y = stoi(ss[2]);
                Continent *TerritoryContinent = getContinentByName(theMap->getContinent(), ss[3]);
                Territory *ptrTerritory =new Territory (nameOfTerritory, TerritoryContinent, x, y) ;
                theMap->pushTerritory(ptrTerritory);
                ss.clear();
            }
        }
    }
    cout << theMap->getContinent().size() << endl;
    cout << theMap->getTerritory().size() << endl;
    if (theMap->getContinent().size() == 0 || theMap->getTerritory().size() == 0) // invlaide use of vector
    {
        cout << "File is missing informations and it is not valid" << endl;
        return nullptr;
    }
    else
    {
        reader.clear(); 
            reader.seekg(0, ios::beg); 
             ss.clear();

        while (getline(reader, line))
        {
            if (line == "[Territories]")
            {
                cout<<"we reached it again"<<endl;
                while (getline(reader, line))
                {

                    stringstream s(line);
                    while (getline(s, token, tDelimiter))
                    {
                        ss.push_back(token);
                    }
                    if (ss.size() > 3)
                    {
                        Territory *currentTerritory = getTerritoryByName(theMap->getTerritory(), ss[0]);
                        for (int i = 4; i < ss.size(); i++)
                        {
                            Territory *ptrT =   getTerritoryByName(theMap->getTerritory(), ss[i]);
                           currentTerritory->pushATerritoryToAdj(ptrT);
                        }
                    }
                    ss.clear();
                }
            }
        }
    }
    cout << "Returned" << endl;
    return theMap;
}
void Territory :: pushATerritoryToAdj(Territory * T){
    adjacentTerritory.push_back(T);
}
Territory *Maploader::getTerritoryByName(vector<Territory *> territories, string name)
{
    for (int i = 0; i < territories.size(); i++)
    {
        if (territories[i]->getNameOfTerritory() == name){ // private name of territory
            return territories[i];}

    }
    return nullptr;
}

void Map::depthFirstSearch(vector<string> &v1, Territory *T1) // private Method, it returns valuable information
{
    vector<Territory *> adjacent = T1->getAdjacentTerritory();

    if (find(v1.begin(), v1.end(), T1->getNameOfTerritory()) != v1.end())
        return; // base case

    v1.push_back(T1->getNameOfTerritory());

    for (int i = 0; i < adjacent.size(); i++)
    {
        depthFirstSearch(v1, adjacent[i]);
    }
}

void Map::dfs_continent(vector<string> &visitedTerritoriesNames, Territory *currentTerritory,
                        Continent *currentContinent)
{

    // Need to remove adjacent territories that aren't in the current continent
    vector<Territory *> currentAdjacentTerritoriesInContinent;
    for (int i = 0; i < currentTerritory->getAdjacentTerritory().size(); i++)
    {
        if (currentTerritory->getAdjacentTerritory().at(i)->getContinent() == currentContinent)
        {
            currentAdjacentTerritoriesInContinent.push_back(currentTerritory->getAdjacentTerritory().at(i));
        }
    }

    // Base case: if current territory has already been visited, return
    if (std::find(visitedTerritoriesNames.begin(), visitedTerritoriesNames.end(), currentTerritory->getTerritoryName()) != visitedTerritoriesNames.end())
    {
        return;
    }

    // Add current territory to visited territories
    visitedTerritoriesNames.push_back(currentTerritory->getTerritoryName());

    for (int i = 0; i < currentAdjacentTerritoriesInContinent.size(); i++)
    {
        // Recursive call to perform DFS for each adjacent territory
        dfs_continent(visitedTerritoriesNames, currentAdjacentTerritoriesInContinent.at(i), currentContinent);
    }
}

vector<Territory *> Map::getTerritoryByContinent(Continent *C)
{
    vector<Territory *> continentTerritories;
    for (auto T : theTerritories)
    {
        if (T->getContinent()->getNameOfContinent() == C->getNameOfContinent())
            continentTerritories.push_back(T);
    }
    return continentTerritories;
}

bool Map::isConnectedTerritory()
{
    vector<Territory *> allTerritory = getTerritory();
    vector<string> decider;

    for (auto T : allTerritory)
    {
        depthFirstSearch(decider, T);
    }
    if (decider.size() == allTerritory.size())
    {
        return true;
    }
    return false;
}

bool Map::isConnectedContinent()
{
    map<string, bool> continentConnected;
    for (int i = 0; i < theContinents.size(); i++)
    {
        continentConnected.insert(pair<string, bool>(theContinents.at(i)->getNameOfContinent(), false));
    }
    for (int i = 0; i < theContinents.size(); i++)
    {
        Continent *currentContinent = theContinents[i];
        vector<Territory *> continentTerritories = getTerritoryByContinent(currentContinent);
        vector<string> visitedTerritories;

        for (auto T : continentTerritories)
        {
            dfs_continent(visitedTerritories, T, currentContinent);

            if (visitedTerritories.size() == continentTerritories.size())
            {
                continentConnected.find(currentContinent->getNameOfContinent())->second = true;
                break;
            }
            visitedTerritories.clear();
        }
    }
    for (auto C : continentConnected)
    {
        if (C.second == false)
            return false;
    }
    cout << "it is connected subgraphs" << endl;
    return true;
}

// Map::Map()
// {
//  theContinents = nullptr;
//  theTerritories=nullptr;
// }

Map::Map()
{
    forTrying = 0;
}

Map::Map(vector<Territory *> theTerritories1, vector<Continent *> theContinents1)
{
    theTerritories = theTerritories1;
    theContinents = theContinents1;
}

void Map::pushContinent(Continent *C)
{
    theContinents.push_back(C);
}

vector<Continent *> Map::getContinent()
{
    return theContinents;
}

void Map::pushTerritory(Territory *T)
{
    theTerritories.push_back(T);
}

vector<Territory *> Map::getTerritory()
{
    return theTerritories;
}

void Map::validate()
{
    if (isConnectedContinent() && isConnectedTerritory())
    {
        cout << "The map is connected" << endl;
    }
    else
    {
        cout << "The map is not connected" << endl;
    }
}

Continent *Maploader::getContinentByName(vector<Continent *> continents, string name)
{
     for (int i = 0; i < continents.size(); i++)
    {
        if (continents.at(i)->getNameOfContinent()==name){
        return continents.at(i);}
    }
    return nullptr;
}

Territory::Territory()
{
    nameOfTerritory = "";
    continent = nullptr;
    x = 0;
    y = 0;
}

Territory::Territory(string name, Continent *theContinent, int z, int w)
{
    nameOfTerritory = name;
    continent = theContinent;
    x = z;
    y = w;
}

vector<Territory *> Territory::getAdjacentTerritory()
{
    return adjacentTerritory;
}

int* Territory::getNumArmies(){
    return numOfArmies;
}

string Territory::getNameOfTerritory()
{
    return nameOfTerritory;
}

Continent *Territory::getContinent()
{
    return continent;
}

string Territory::getTerritoryName()
{
    return nameOfTerritory;
}

Continent::Continent()
{
    nameOfContinent = "";
}

Continent::Continent(string name)
{
    nameOfContinent = "name";
}

Continent::Continent(string name, int bonus)
{
    nameOfContinent = name;
    controlBonus = bonus;
}

string Continent::getNameOfContinent()
{
    return nameOfContinent;
}

int Continent::getControlBonus() const
{
    return controlBonus;
}
