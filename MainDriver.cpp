#include "CardsDriver.h"
#include "GameEngineDriver.h"
#include "PlayerDriver.h"
#include "MapDriver.h"
#include "OrdersDriver.h"

#include <iostream>

int main() {

    // Loads Map
    testLoadMaps();

    // Loads Players
    testPlayers();

    // Loads Order List
    testOrdersLists();

    // Loads Cards
    testCards();

    // Game Engine
    testGameStates();

    return 0;
}
