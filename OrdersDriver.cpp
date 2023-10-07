#include "OrdersDriver.h"
#include "Orders.h"
//#include "Player.h"
//#include "Cards.h"
//#include "Map.h"
#include <iostream>

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
    testOrdersLists();
    return 0;
}*/
