// Orders.h

#ifndef ORDERS_H
#define ORDERS_H

#include <string>
#include <list>
#include <iostream>

// Forward declaration
class OrdersList;

// Base Order class
class Order {
protected:
    std::string description;
    std::string effect;

public:
    Order();
    virtual ~Order();

    virtual bool validate() = 0; // Pure virtual function
    virtual void execute() = 0; // Pure virtual function
    virtual Order* clone() const = 0; // Pure virtual function


    friend std::ostream& operator<<(std::ostream& out, const Order& order);

    // Copy constructor and assignment operator
    Order(const Order& other);
    Order& operator=(const Order& other);
};

// Subclasses for each order type
class Deploy : public Order {

private:
    int numUnits;
    std::string targetTerritory;
public:
    Deploy(); // Default constructor declaration
    Deploy(int units, const std::string territory); // Parameterized constructor declaration
    bool validate() override;
    void execute() override;
    Deploy(const Deploy& other);  // Copy constructor declaration
    Deploy* clone() const override;  // Clone method declaration

    friend std::ostream& operator<<(std::ostream& out, const Deploy& deploy);  // Stream insertion operator declaration
    Deploy& operator=(const Deploy& other); // Assignment operator


};

class Advance : public Order {

private: 
    int numUnits;
    std::string sourceTerritory;
    std::string targetTerritory;
public:
    Advance();
    Advance(int units, const std::string source, const std::string target); // Parameterized constructor declaration
    bool validate() override;
    void execute() override;
    Advance(const Advance& other);  // Copy constructor declaration
    Advance* clone() const override;  // Clone method declaration

    friend std::ostream& operator<<(std::ostream& out, const Advance& advance);  // Stream insertion operator declaration
    Advance& operator=(const Advance& other); // Assignment operator

};


class Bomb : public Order {

private:
    std::string targetTerritory;
    bool hasBombCard;
public:
    Bomb();
    Bomb(const std::string target, bool hasCard); // Parameterized constructor declaration
    bool validate() override;
    void execute() override;
    Bomb(const Bomb& other);  // Copy constructor declaration
    Bomb* clone() const override;  // Clone method declaration

    friend std::ostream& operator<<(std::ostream& out, const Bomb& bomb);  // Stream insertion operator declaration
    Bomb& operator=(const Bomb& other); // Assignment operator

};

class Blockade : public Order {

private:
    std::string targetTerritory;
    bool hasBlockadeCard;
public:
    Blockade();
    Blockade(const std::string target, bool hasCard); // Parameterized constructor declaration
    bool validate() override;
    void execute() override;    
    Blockade(const Blockade& other);  // Copy constructor declaration
    Blockade* clone() const override;  // Clone method declaration

    friend std::ostream& operator<<(std::ostream& out, const Blockade& blockade);  // Stream insertion operator declaration
    Blockade& operator=(const Blockade& other); // Assignment operator

};

class Airlift : public Order {

private:
    int numUnits;
    std::string sourceTerritory;
    std::string targetTerritory;
    bool hasAirliftCard;
public:
    Airlift();
    Airlift(int units, const std::string source, const std::string target, bool hasCard); // Parameterized constructor declaration
    bool validate() override;
    void execute() override;
    Airlift(const Airlift& other);  // Copy constructor declaration
    Airlift* clone() const override;  // Clone method declaration

    friend std::ostream& operator<<(std::ostream& out, const Airlift& airlift);  // Stream insertion operator declaration
    Airlift& operator=(const Airlift& other); // Assignment operator

};

class Negotiate : public Order {

private:
    std::string targetPlayer;
    bool hasDiplomacyCard;
public:
    Negotiate();
    Negotiate(const std::string target, bool hasCard); // Parameterized constructor declaration
    bool validate() override;
    void execute() override;
    Negotiate(const Negotiate& other);  // Copy constructor declaration
    Negotiate* clone() const override;  // Clone method declaration

    friend std::ostream& operator<<(std::ostream& out, const Negotiate& negotiate);  // Stream insertion operator declaration
    Negotiate& operator=(const Negotiate& other); // Assignment operator

};

class OrdersList {
private:
    std::list<Order*> orders;

public:
    OrdersList();
    ~OrdersList();

    void addOrder(Order* order);
    void remove(Order* order);
    void move(Order* order, int position);

    // Copy constructor and assignment operator and stream insertion operator
    friend std::ostream& operator<<(std::ostream& out, const OrdersList& ordersList);
    OrdersList(const OrdersList& other);
    OrdersList& operator=(const OrdersList& other);
};

#endif // ORDERS_H
