#include "Orders.h"
//#include "Player.h"
//#include "Cards.h"
//#include "Map.h"


// Order class implementations

// Default constructor
Order::Order() : description(""), effect("") {}

// Destructor
Order::~Order() {}

// Parameterized constructor
Order::Order(const Order& other) : description(other.description), effect(other.effect) {}

// Assignment operator of the base class order 
Order& Order::operator=(const Order& other) {
    if (this != &other) {
        description = other.description;
        effect = other.effect;
    }
    return *this;
}

// Print method useful for the stream insertion operator
void Order::print(std::ostream& out) const {
    out << description;
    if (!effect.empty()) {
        out << "  |  Effect: " << effect;
    }
}

// Stream insertion operator
std::ostream& operator<<(std::ostream& out, const Order& order) {
    order.print(out);
    return out;
}


// Deploy class implementations

// Default constructor
Deploy::Deploy() : numUnits(0), targetTerritory("") {
    description = "Deploy Order";
}

// Parameterized constructor
Deploy::Deploy(int units, const std::string territory) : numUnits(units), targetTerritory(territory) {
    description = "Deploy Order";
}

// Destructor
Deploy::~Deploy() {}

//Copy constructor
Deploy::Deploy(const Deploy& other) : Order(other), numUnits(other.numUnits), targetTerritory(other.targetTerritory) {}

// Clone method
Deploy* Deploy::clone() const {
    return new Deploy(*this);
}

// Validate method
bool Deploy::validate() {
  return true;
}
// for the moment i am simply implementing a trivial validate method, for the testing
/*
bool Deploy::validate() {
    // Assuming player is a pointer to the Player object for the player issuing the order
    // and targetTerritory is a pointer to the Territory object for the target territory
    if (!targetTerritory->belongsTo(player)) {
        return false;
    }
    if (numUnits <= 0 || numUnits > player->hasAvailableReinforcements()) {
        return false;
    }
    return true;
}
*/

// Execute method
void Deploy::execute() {
    if (validate()) {
        // Add units to targetTerritory
        effect = "Deployed " + std::to_string(numUnits) + " units to " + targetTerritory;
    }
}


// Print method useful for the stream insertion operator
void Deploy::print(std::ostream& out) const {
    Order::print(out);  // Call the superclass's print function
    out << "  |  Units: " << numUnits 
        << "  |  Target Territory: " << targetTerritory;
}

// Stream insertion operator for deploy order
std::ostream& operator<<(std::ostream& out, const Deploy& deploy) {
    deploy.print(out);
    return out;
}


// Assignment operator of the Deploy order 
Deploy& Deploy::operator=(const Deploy& other) {
    if (this != &other) {
        Order::operator=(other); // Call base class assignment operator
        numUnits = other.numUnits;
        targetTerritory = other.targetTerritory;
    }
    return *this;
}

// Advance class implementations


// Default constructor
Advance::Advance() : numUnits(0), sourceTerritory(""), targetTerritory("") {
    description = "Advance Order";
}

// Parameterized constructor
Advance::Advance(int units, const std::string source, const std::string target) 
    : numUnits(units), sourceTerritory(source), targetTerritory(target) {
    description = "Advance Order";
}

// Copy constructor
Advance::Advance(const Advance& other) 
    : Order(other), 
      numUnits(other.numUnits), 
      sourceTerritory(other.sourceTerritory), 
      targetTerritory(other.targetTerritory) {}


// Destructor
Advance::~Advance() {}

// Clone method
Advance* Advance::clone() const {
    return new Advance(*this);
}

// Validate method
bool Advance::validate() {
  return true;
}
// for the moment i am simply implementing a trivial validate method, for the testing
/*
bool Advance::validate() {
    if (!sourceTerritory->isAdjacentTo(targetTerritory)) {
        return false;
    }
    if (numUnits <= 0 || numUnits > sourceTerritory->getUnitCount()) {
        return false;
    }
    return true;
}

*/

// Execute method
void Advance::execute() {
    if (validate()) {
        // Move units from sourceTerritory to targetTerritory
        effect = "Advanced " + std::to_string(numUnits) + " units from " + sourceTerritory + " to " + targetTerritory;
    }
}

// Print method useful for the stream insertion operator
void Advance::print(std::ostream& out) const {
    Order::print(out);
    out << "  |  Units: " << numUnits 
        << "  |  Source Territory: " << sourceTerritory 
        << "  |  Target Territory: " << targetTerritory;
}

// Stream insertion operator for advance order
std::ostream& operator<<(std::ostream& out, const Advance& advance) {
    advance.print(out);
    return out;
}


// Assignment operator of the advance order 
Advance& Advance::operator=(const Advance& other) {
    if (this != &other) {
        Order::operator=(other);
        numUnits = other.numUnits;
        sourceTerritory = other.sourceTerritory;
        targetTerritory = other.targetTerritory;
    }
    return *this;
}


// Bomb class implementations

// Default constructor
Bomb::Bomb() : targetTerritory(""), hasBombCard(false) {
    description = "Bomb Order";
}

// Parameterized constructor
Bomb::Bomb(const std::string target, bool hasCard) : targetTerritory(target), hasBombCard(hasCard) {
    description = "Bomb Order";
}

// Copy constructor
Bomb::Bomb(const Bomb& other) 
    : Order(other), 
      targetTerritory(other.targetTerritory), 
      hasBombCard(other.hasBombCard) {}

// Destructor
Bomb::~Bomb() {}

// Clone method
Bomb* Bomb::clone() const {
    return new Bomb(*this);
}

// Validate method
bool Bomb::validate() {
  return true;
}

// for the moment i am simply implementing a trivial validate method, for the testing
/*
bool Bomb::validate() {
    if (!player->hasCard(bomb)) {
        return false;
    }
    if (targetTerritory->belongsTo(player)) {
        return false;
    }
    bool isAdjacent = false;
    for (Territory* ownedTerritory : player->getTerritories()) {
        if (ownedTerritory->isAdjacentTo(targetTerritory)) {
            isAdjacent = true;
            break;
        }
    }
    if (!isAdjacent) {
        return false;
    }
    return true;
}

*/

// Execute method
void Bomb::execute() {
    if (validate()) {
        // Halve the units on targetTerritory
        effect = "Bombed " + targetTerritory;
    }
}


// Print method useful for the stream insertion operator
void Bomb::print(std::ostream& out) const {
    Order::print(out);
    out << "  |  Target Territory: " << targetTerritory 
        << "  |  Has Bomb Card: " << (hasBombCard ? "Yes" : "No");
}

// Stream insertion operator for bomb order
std::ostream& operator<<(std::ostream& out, const Bomb& bomb) {
    bomb.print(out);
    return out;
}


// Assignment operator of the bomb order 
Bomb& Bomb::operator=(const Bomb& other) {
    if (this != &other) {
        Order::operator=(other);
        targetTerritory = other.targetTerritory;
        hasBombCard = other.hasBombCard;
    }
    return *this;
}

// Blockade class implementations

// Default constructor
Blockade::Blockade() : targetTerritory(""), hasBlockadeCard(false) {
    description = "Blockade Order";
}

// Parameterized constructor
Blockade::Blockade(const std::string target, bool hasCard) : targetTerritory(target), hasBlockadeCard(hasCard) {
    description = "Blockade Order";
}

// Copy constructor
Blockade::Blockade(const Blockade& other) 
    : Order(other), 
      targetTerritory(other.targetTerritory), 
      hasBlockadeCard(other.hasBlockadeCard) {}



// Destructor
Blockade::~Blockade() {}

// Clone method
Blockade* Blockade::clone() const {
    return new Blockade(*this);
}

// Validate method
bool Blockade::validate() {
  return true;
}

// for the moment i am simply implementing a trivial validate method, for the testing
/*
bool Blockade::validate() {
    if (!player->hasCard(blockade)) {
        return false;
    }
    if (!targetTerritory->belongsTo(player)) {
        return false;
    }
    return true;
}
*/

// Execute method
void Blockade::execute() {
    if (validate()) {
        // Triple the units on targetTerritory and make it neutral
        effect = "Blockaded " + targetTerritory;
    }
}

// Print method useful for the stream insertion operator
void Blockade::print(std::ostream& out) const {
    Order::print(out);
    out << "  |  Target Territory: " << targetTerritory 
        << "  |  Has Blockade Card: " << (hasBlockadeCard ? "Yes" : "No");
}

// Stream insertion operator for blockade order
std::ostream& operator<<(std::ostream& out, const Blockade& blockade) {
    blockade.print(out);
    return out;
}


// Assignment operator of the blockade order 
Blockade& Blockade::operator=(const Blockade& other) {
    if (this != &other) {
        Order::operator=(other);
        targetTerritory = other.targetTerritory;
        hasBlockadeCard = other.hasBlockadeCard;
    }
    return *this;
}

// Airlift class implementations

// Default constructor
Airlift::Airlift() : numUnits(0), sourceTerritory(""), targetTerritory(""), hasAirliftCard(false) {
    description = "Airlift Order";
}

// Parameterized constructor
Airlift::Airlift(int units, const std::string source, const std::string target, bool hasCard) 
    : numUnits(units), sourceTerritory(source), targetTerritory(target), hasAirliftCard(hasCard) {
    description = "Airlift Order";
}

// Copy constructor
Airlift::Airlift(const Airlift& other) 
    : Order(other), 
      numUnits(other.numUnits), 
      sourceTerritory(other.sourceTerritory), 
      targetTerritory(other.targetTerritory), 
      hasAirliftCard(other.hasAirliftCard) {}



// Destructor
Airlift::~Airlift() {}


// Clone method
Airlift* Airlift::clone() const {
    return new Airlift(*this);
}

// Validate method
bool Airlift::validate() {
  return true;
}
// for the moment i am simply implementing a trivial validate method, for the testing
/*
bool Airlift::validate() {
    if (!player->hasCard(airlift)) {
        return false;
    }
    if (!sourceTerritory->belongsTo(player)) {
        return false;
    }
    if (numUnits <= 0 || numUnits > sourceTerritory->getUnitCount()) {
        return false;
    }
    return true;
}
*/

// Execute method
void Airlift::execute() {
    if (validate()) {
        // Move units from sourceTerritory to targetTerritory
        effect = "Airlifted " + std::to_string(numUnits) + " units from " + sourceTerritory + " to " + targetTerritory;
    }
}

// Print method useful for the stream insertion operator
void Airlift::print(std::ostream& out) const {
    Order::print(out);
    out << "  |  Units: " << numUnits 
        << "  |  Source Territory: " << sourceTerritory 
        << "  |  Target Territory: " << targetTerritory 
        << "  |  Has Airlift Card: " << (hasAirliftCard ? "Yes" : "No");
}


// Stream insertion operator for airlift order
std::ostream& operator<<(std::ostream& out, const Airlift& airlift) {
    airlift.print(out);
    return out;
}


// Assignment operator of the airlift order 
Airlift& Airlift::operator=(const Airlift& other) {
    if (this != &other) {
        Order::operator=(other);
        numUnits = other.numUnits;
        sourceTerritory = other.sourceTerritory;
        targetTerritory = other.targetTerritory;
        hasAirliftCard = other.hasAirliftCard;
    }
    return *this;
}

// Negotiate class implementations

// Default constructor
Negotiate::Negotiate() : targetPlayer(""), hasDiplomacyCard(false) {
    description = "Negotiate Order";
}

// Parameterized constructor
Negotiate::Negotiate(const std::string target, bool hasCard) : targetPlayer(target), hasDiplomacyCard(hasCard) {
    description = "Negotiate Order";
}

// Copy constructor
Negotiate::Negotiate(const Negotiate& other) 
    : Order(other), 
      targetPlayer(other.targetPlayer), 
      hasDiplomacyCard(other.hasDiplomacyCard) {}


// Destructor
Negotiate::~Negotiate() {}

// Clone method
Negotiate* Negotiate::clone() const {
    return new Negotiate(*this);
}

// Validate method
bool Negotiate::validate() {
  return true;
}

// for the moment i am simply implementing a trivial validate method, for the testing
/*
bool Negotiate::validate() {
    if (!player->hasCard(diplomacy)) {
        return false;
    }
    if (targetPlayer == player) {
        return false;
    }
    return true;
}
*/

// Execute method
void Negotiate::execute() {
    if (validate()) {
        // Prevent attacks between current player and targetPlayer
        effect = "Negotiated with " + targetPlayer;
    }
}


// Print method useful for the stream insertion operator
void Negotiate::print(std::ostream& out) const {
    Order::print(out);
    out << "  |  Target Player: " << targetPlayer 
        << "  |  Has Diplomacy Card: " << (hasDiplomacyCard ? "Yes" : "No");
}

// Stream insertion operator for negotiate order
std::ostream& operator<<(std::ostream& out, const Negotiate& negotiate) {
    negotiate.print(out);
    return out;
}

// Assignment operator of the negotiate order 
Negotiate& Negotiate::operator=(const Negotiate& other) {
    if (this != &other) {
        Order::operator=(other);
        targetPlayer = other.targetPlayer;
        hasDiplomacyCard = other.hasDiplomacyCard;
    }
    return *this;
}

// OrdersList class implementations
OrdersList::OrdersList() {}


// Destructor of the orders list
OrdersList::~OrdersList() {
    for (Order* order : orders) {
        delete order;
    }
    orders.clear();
}

// Getter method to return the pointer to an order inside the list
const std::list<Order*>& OrdersList::getOrders() const {
    return orders;
}

// Method to add orders inside the list
void OrdersList::addOrder(Order* order) {
    orders.push_back(order);
}


void OrdersList::remove(int index) {
    if (index < 0 || index >= orders.size()) {
        std::cerr << "Invalid index provided for removal operation." << std::endl;
        return;
    }
    std::list<Order*>::iterator it = std::next(orders.begin(), index);
    delete *it;
    orders.erase(it);
}




void OrdersList::move(int sourceIndex, int targetIndex) {
    // Check if the indices are valid
    if (sourceIndex < 0 || sourceIndex >= orders.size() || targetIndex < 0 || targetIndex > orders.size()) {
        std::cerr << "Invalid indices provided for move operation." << std::endl;
        return;
    }

    // Get the order at the source index
    std::list<Order*>::iterator sourceIt = std::next(orders.begin(), sourceIndex);
    Order* orderToMove = *sourceIt;

    // Remove the order from the list (without deleting it)
    orders.erase(sourceIt);

    // Insert the order at the target index
    std::list<Order*>::iterator targetIt = std::next(orders.begin(), targetIndex);
    orders.insert(targetIt, orderToMove);
}



// Copy constructor for the orders list
OrdersList::OrdersList(const OrdersList& other) {
    for (Order* order : other.orders) {
        orders.push_back(order->clone());
    }
}

// Assignment operator for the orders list
OrdersList& OrdersList::operator=(const OrdersList& other) {
    if (this != &other) {
        // First, delete the existing orders in the current object
        for (Order* order : orders) {
            delete order;
        }
        orders.clear();

        // Now, copy orders from the other OrdersList using the clone method
        for (Order* order : other.orders) {
            orders.push_back(order->clone());
        }
    }
    return *this;
}


// Stream insertion operator for the orders list
std::ostream& operator<<(std::ostream& out, const OrdersList& ordersList) {
    out << "Orders List:" << std::endl;
    for (const Order* order : ordersList.orders) {
        out << *order << std::endl;
    }
    return out;
}
