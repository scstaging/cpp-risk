#include "Map.h"
#include "MapDriver.h"
#include <iostream>
using namespace std;

void testLoadMaps() {

Maploader x;
Map* pleaseWork = x.readFiles("map1.map");
vector <Territory*> y = pleaseWork->getTerritory();
// for (int i =0; i<y.size(); i++){
//     string name = y.at(i)->getNameOfTerritory();
//     cout<<name<<endl;
vector <Territory*> adj = y.at(1)->getAdjacentTerritory();
cout<<adj.size()<<endl;
for (int i =0; i<adj.size();i++){
    cout<< adj.at(i)->getNameOfTerritory()<<endl;
    }
    cout<<"fejrknfkjenfef";
    pleaseWork->validate();
}
