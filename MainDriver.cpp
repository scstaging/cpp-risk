#include <iostream>
#include <MainDriver.h>
#include <PlayerDriver.h>

int main() {

    // Loads Map
    testLoadMaps();

    // Loads Players
    testPlayers();

    // Loads Order List
    testOrdersList();

    // Loads Cards
    testCards();

    // Game Engine
    testGameStates();

    return 0;
}
