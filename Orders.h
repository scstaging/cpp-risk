#ifndef ORDERS_H
#define ORDERS_H
#include "Map.h"
#include "Player.h"
#include "Cards.h"
#include "GameEngine.h"

#include <string>
#include <list>
#include <iostream>

// Forward declaration
class OrdersList;

// Base Order class
class Order
{
protected:
    std::string description;
    std::string effect;

public:
    Order();
    virtual ~Order();

    virtual bool validate() = 0;                     // Pure virtual function
    virtual void execute() = 0;                      // Pure virtual function
    virtual Order *clone() const = 0;                // Pure virtual function
    virtual void print(std::ostream &out) const = 0; // Print function useful for the stream insertion operator

    friend std::ostream &operator<<(std::ostream &out, const Order &order); // Stream insertion operator

    // Copy constructor and assignment operator
    Order(const Order &other);
    Order &operator=(const Order &other);
};

// Subclasses for each order type
class Deploy : public Order
{

private:
    Player *player;
    Territory *territory; // Pointer to the target territory
    std::string targetTerritoryName;
    GameEngine *game;
    int numOfArmies;

public:
    Deploy(Player *player, std::string targetTerritoryName, GameEngine *game, int numOfArmies); // Parameterized constructor declaration
    // Other members and methods...
    ~Deploy(); // Destructor
    bool validate() override;
    void execute() override;
    Deploy(const Deploy &other);                  // Copy constructor declaration
    Deploy *clone() const override;               // Clone method declaration
    void print(std::ostream &out) const override; // Print function useful for the stream insertion operator

    friend std::ostream &operator<<(std::ostream &out, const Deploy &deploy); // Stream insertion operator declaration
    Deploy &operator=(const Deploy &other);                                   // Assignment operator
};

class Advance : public Order
{

private:
    Player *player;
    GameEngine *game;
    int numUnits;
    Territory *srcTerritory;
    Territory *trgtTerritory;
    std::string sourceTerritory;
    std::string targetTerritory;

public:
    Advance(Player *player, std::string sourceTerritoryName, std::string targetTerritoryName, GameEngine *game, int units); // Parameterized constructor declaration
    ~Advance();                                                                                                             // Destructor
    bool validate() override;
    void execute() override;
    Advance(const Advance &other);                                              // Copy constructor declaration
    Advance *clone() const override;                                            // Clone method declaration
    void print(std::ostream &out) const override;                               // Print function useful for the stream insertion operator
    friend std::ostream &operator<<(std::ostream &out, const Advance &advance); // Stream insertion operator declaration
    Advance &operator=(const Advance &other);                                   // Assignment operator
};

class Bomb : public Order
{

private:
    std::string targetTerritory;
    Territory *trgtTerritory;
    Map *map;
    Player *player;
    GameEngine *game;

public:
    Bomb(Player *player, std::string targetTerritoryName, GameEngine *game, Map *map); // Parameterized constructor declaration
    ~Bomb();                                                                           // Destructor
    bool validate() override;
    void execute() override;
    Bomb(const Bomb &other);                      // Copy constructor declaration
    Bomb *clone() const override;                 // Clone method declaration
    void print(std::ostream &out) const override; // Print function useful for the stream insertion operator

    friend std::ostream &operator<<(std::ostream &out, const Bomb &bomb); // Stream insertion operator declaration
    Bomb &operator=(const Bomb &other);                                   // Assignment operator
};

class Blockade : public Order
{

private:
    std::string targetTerritory;
    Player *player;
    GameEngine *game;
    Territory *trgtTerritory;

public:
    Blockade(Player *player, std::string targetTerritoryName, GameEngine *game); // Parameterized constructor declaration
    ~Blockade();                                                                 // Destructor
    bool validate() override;
    void execute() override;
    Blockade(const Blockade &other);                                              // Copy constructor declaration
    Blockade *clone() const override;                                             // Clone method declaration
    void print(std::ostream &out) const override;                                 // Print function useful for the stream insertion operator
    friend std::ostream &operator<<(std::ostream &out, const Blockade &blockade); // Stream insertion operator declaration
    Blockade &operator=(const Blockade &other);                                   // Assignment operator
};

class Airlift : public Order
{

private:
    GameEngine *game;
    Player *player;
    Territory *srcTerritory;
    Territory *trgtTerritory;
    int numUnits;
    std::string sourceTerritory;
    std::string targetTerritory;

public:
    Airlift(Player *player, std::string sourceTerritoryName, std::string targetTerritoryName, GameEngine *game, int units); // Parameterized constructor declaration
    ~Airlift();                                                                                                             // Destructor
    bool validate() override;
    void execute() override;
    Airlift(const Airlift &other);                // Copy constructor declaration
    Airlift *clone() const override;              // Clone method declaration
    void print(std::ostream &out) const override; // Print function useful for the stream insertion operator

    friend std::ostream &operator<<(std::ostream &out, const Airlift &airlift); // Stream insertion operator declaration
    Airlift &operator=(const Airlift &other);                                   // Assignment operator
};

class Negotiate : public Order
{

private:
    Player *player;
    Player *targetPlayer;
    GameEngine *game;

public:
    Negotiate(Player *player, Player *targetPlayer, GameEngine *game); // Parameterized constructor declaration
    ~Negotiate();                                                      // Destructor
    bool validate() override;
    void execute() override;
    Negotiate(const Negotiate &other);            // Copy constructor declaration
    Negotiate *clone() const override;            // Clone method declaration
    void print(std::ostream &out) const override; // Print function useful for the stream insertion operator

    friend std::ostream &operator<<(std::ostream &out, const Negotiate &negotiate); // Stream insertion operator declaration
    Negotiate &operator=(const Negotiate &other);                                   // Assignment operator
};

class OrdersList
{
private:
    std::list<Order *> orders;

public:
    OrdersList();
    ~OrdersList();

    // Method to add orders
    void addOrder(Order *order);

    // Method to move an order inside the list
    void move(int sourceIndex, int targetIndex);

    // Method to remove an order from the list
    void remove(int index);

    const std::list<Order *> &getOrders() const; // Getting the orders list

    // Copy constructor and assignment operator and stream insertion operator
    friend std::ostream &operator<<(std::ostream &out, const OrdersList &ordersList);
    OrdersList(const OrdersList &other);
    OrdersList &operator=(const OrdersList &other);
};

#endif // ORDERS_H
