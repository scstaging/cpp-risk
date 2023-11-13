#include "OrdersDriver.h"
#include "Orders.h"
#include "Player.h"
#include "Cards.h"
#include "Map.h"
#include <iostream>
void testOrderExecution(){
GameEngine *game = new GameEngine();

    Maploader maploader;

    Map *map = maploader.readFiles("map1.map");
    // get all the territories
    vector<Territory *> map_territories = map->getTerritory();

    cout << "**** Create a player and assign the territory ****\n";

    Territory *territory = map_territories[0]; // For simplicity, choose the first territory

    cout << "**** Create a player and assign the territory ****\n";
    // Create a player and assign the territory
    Player *player = new Player("Player1");
    std::vector<Territory *> playerTerritories = {territory};
    player->setTerritories(playerTerritories);

    // Set up the initial number of armies in the territory
    int initialArmies = 5;
    *(territory->getNumArmies()) = initialArmies;

    // Set up the player's reinforcements
    int reinforcements = 3;
    player->incrementReinforcementPool(reinforcements);

    // Create a Deploy order
    int deployArmies = 2;
    std::string targetTerritoryName = "Sample Territory";
    Deploy *deployOrder = new Deploy(player, targetTerritoryName, deployArmies);
    // Validate and execute the Deploy order
    if (deployOrder->validate())
    {
        deployOrder->execute();
        std::cout << "Deploy order executed successfully." << std::endl;
        std::cout << "New number of armies in " << targetTerritoryName << ": " << *(territory->getNumArmies()) << std::endl;
    }
    // Clean up dynamically allocated resources
    delete deployOrder;
    delete player;
    delete map;
    delete game;
}
void testOrdersLists() {

    // Create an OrdersList object
    OrdersList ordersList;

    // Create orders of every kind and add them to the OrdersList
    ordersList.addOrder(new Deploy(5, "TerritoryA"));
    ordersList.addOrder(new Advance(3, "TerritoryA", "TerritoryB"));
    ordersList.addOrder(new Bomb("TerritoryC", true));
    ordersList.addOrder(new Blockade("TerritoryD", true));
    ordersList.addOrder(new Airlift(4, "TerritoryE", "TerritoryF", true));
    ordersList.addOrder(new Negotiate("Player2", true));

    std::cout << "\nDisplaying the Orders List without the effects first since there has been no execution...\n";

    // Display the OrdersList
    std::cout << ordersList << std::endl;
    
    std::cout << "Testing validate() on each order in the list\n";

    // Test validate() on each order in the list
    for (Order* order : ordersList.getOrders()) {
        if (order->validate()) {
            std::cout << "Order is valid: " << *order << std::endl;
        } else {
            std::cout << "Order is invalid: " << *order << std::endl;
        }
    }

    std::cout << "\nTesting execute() on each order in the list, effects should appear this time...\n";
    // Execute each order in the list
    for (Order* order : ordersList.getOrders()) {
        if (order->validate()) { // It's still a good idea to check if the order is valid before executing
            order->execute();
            std::cout << "Executed order: " << *order << std::endl;
        } else {
            std::cout << "Skipped execution of invalid order: " << *order << std::endl;
        }
    }

    // Demonstrate move() functionality
    std::cout << "\nMoving the Bomb order to the front of the list...\n";
    ordersList.move(2, 0);  // Move the order at index 2 to the front of the list
    std::cout << ordersList << std::endl;

    // Demonstrate remove() functionality
    std::cout << "\nRemoving the Bomb order from the list...\n";
    ordersList.remove(0);  // Remove the order at index 0 (which is the Bomb order after the move operation)
    std::cout << ordersList << std::endl;

    

  
}
/*
int main() {
    testOrderExecution();
    testOrdersLists();
    return 0;
}*/
