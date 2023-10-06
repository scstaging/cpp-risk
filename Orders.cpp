// Orders.cpp

#include "Orders.h"

// Order class implementations
Order::Order() : description(""), effect("") {}

Order::~Order() {}

Order::Order(const Order& other) : description(other.description), effect(other.effect) {}

Order& Order::operator=(const Order& other) {
    if (this != &other) {
        description = other.description;
        effect = other.effect;
    }
    return *this;
}

std::ostream& operator<<(std::ostream& out, const Order& order) {
    out << order.description;
    if (!order.effect.empty()) {
        out << " - Effect: " << order.effect;
    }
    return out;
}

// Deploy class implementations

Deploy::Deploy() : numUnits(0), targetTerritory("") {
    description = "Deploy Order";
}
Deploy::Deploy(int units, const std::string territory) : numUnits(units), targetTerritory(territory) {
    description = "Deploy Order";
}

Deploy::Deploy(const Deploy& other) : Order(other), numUnits(other.numUnits), targetTerritory(other.targetTerritory) {}


Deploy* Deploy::clone() const {
    return new Deploy(*this);
}

bool Deploy::validate() {
  return true;
}

/*
bool Deploy::validate() {
    // Assuming player is a pointer to the Player object for the player issuing the order
    // and targetTerritory is a pointer to the Territory object for the target territory
    if (!targetTerritory->belongsTo(player)) {
        return false;
    }
    if (numUnits <= 0 || numUnits > player->getAvailableReinforcements()) {
        return false;
    }
    return true;
}
*/

void Deploy::execute() {
    if (validate()) {
        // Add units to targetTerritory
        effect = "Deployed " + std::to_string(numUnits) + " units to " + targetTerritory;
    }
}

std::ostream& operator<<(std::ostream& out, const Deploy& deploy) {
    out << "Order Type: " << deploy.description 
        << "\nUnits: " << deploy.numUnits 
        << "\nTarget Territory: " << deploy.targetTerritory;
    if (!deploy.effect.empty()) {
        out << "\nEffect: " << deploy.effect;
    }
    return out;
}

Deploy& Deploy::operator=(const Deploy& other) {
    if (this != &other) {
        Order::operator=(other); // Call base class assignment operator
        numUnits = other.numUnits;
        targetTerritory = other.targetTerritory;
    }
    return *this;
}

// Advance class implementations

Advance::Advance() : numUnits(0), sourceTerritory(""), targetTerritory("") {
    description = "Advance Order";
}
Advance::Advance(int units, const std::string source, const std::string target) 
    : numUnits(units), sourceTerritory(source), targetTerritory(target) {
    description = "Advance Order";
}

Advance::Advance(const Advance& other) 
    : Order(other), 
      numUnits(other.numUnits), 
      sourceTerritory(other.sourceTerritory), 
      targetTerritory(other.targetTerritory) {}



Advance* Advance::clone() const {
    return new Advance(*this);
}

bool Advance::validate() {
  return true;
}
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


void Advance::execute() {
    if (validate()) {
        // Move units from sourceTerritory to targetTerritory
        effect = "Advanced " + std::to_string(numUnits) + " units from " + sourceTerritory + " to " + targetTerritory;
    }
}

std::ostream& operator<<(std::ostream& out, const Advance& advance) {
    out << "Order Type: " << advance.description 
        << "\nUnits: " << advance.numUnits 
        << "\nSource Territory: " << advance.sourceTerritory 
        << "\nTarget Territory: " << advance.targetTerritory;
    if (!advance.effect.empty()) {
        out << "\nEffect: " << advance.effect;
    }
    return out;
}

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


Bomb::Bomb() : targetTerritory(""), hasBombCard(false) {
    description = "Bomb Order";
}

Bomb::Bomb(const std::string target, bool hasCard) : targetTerritory(target), hasBombCard(hasCard) {
    description = "Bomb Order";
}


Bomb::Bomb(const Bomb& other) 
    : Order(other), 
      targetTerritory(other.targetTerritory), 
      hasBombCard(other.hasBombCard) {}


Bomb* Bomb::clone() const {
    return new Bomb(*this);
}

bool Bomb::validate() {
  return true;
}

/*
bool Bomb::validate() {
    if (!player->hasCard(BOMB_CARD)) {
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

void Bomb::execute() {
    if (validate()) {
        // Halve the units on targetTerritory
        effect = "Bombed " + targetTerritory;
    }
}

std::ostream& operator<<(std::ostream& out, const Bomb& bomb) {
    out << "Order Type: " << bomb.description 
        << "\nTarget Territory: " << bomb.targetTerritory 
        << "\nHas Bomb Card: " << (bomb.hasBombCard ? "Yes" : "No");
    if (!bomb.effect.empty()) {
        out << "\nEffect: " << bomb.effect;
    }
    return out;
}

Bomb& Bomb::operator=(const Bomb& other) {
    if (this != &other) {
        Order::operator=(other);
        targetTerritory = other.targetTerritory;
        hasBombCard = other.hasBombCard;
    }
    return *this;
}

// Blockade class implementations
Blockade::Blockade() : targetTerritory(""), hasBlockadeCard(false) {
    description = "Blockade Order";
}

Blockade::Blockade(const std::string target, bool hasCard) : targetTerritory(target), hasBlockadeCard(hasCard) {
    description = "Blockade Order";
}

Blockade::Blockade(const Blockade& other) 
    : Order(other), 
      targetTerritory(other.targetTerritory), 
      hasBlockadeCard(other.hasBlockadeCard) {}


Blockade* Blockade::clone() const {
    return new Blockade(*this);
}

bool Blockade::validate() {
  return true;
}

/*
bool Blockade::validate() {
    if (!player->hasCard(BLOCKADE_CARD)) {
        return false;
    }
    if (!targetTerritory->belongsTo(player)) {
        return false;
    }
    return true;
}
*/

void Blockade::execute() {
    if (validate()) {
        // Triple the units on targetTerritory and make it neutral
        effect = "Blockaded " + targetTerritory;
    }
}


std::ostream& operator<<(std::ostream& out, const Blockade& blockade) {
    out << "Order Type: " << blockade.description 
        << "\nTarget Territory: " << blockade.targetTerritory 
        << "\nHas Blockade Card: " << (blockade.hasBlockadeCard ? "Yes" : "No");
    if (!blockade.effect.empty()) {
        out << "\nEffect: " << blockade.effect;
    }
    return out;
}

Blockade& Blockade::operator=(const Blockade& other) {
    if (this != &other) {
        Order::operator=(other);
        targetTerritory = other.targetTerritory;
        hasBlockadeCard = other.hasBlockadeCard;
    }
    return *this;
}

// Airlift class implementations

Airlift::Airlift() : numUnits(0), sourceTerritory(""), targetTerritory(""), hasAirliftCard(false) {
    description = "Airlift Order";
}

Airlift::Airlift(int units, const std::string source, const std::string target, bool hasCard) 
    : numUnits(units), sourceTerritory(source), targetTerritory(target), hasAirliftCard(hasCard) {
    description = "Airlift Order";
}

Airlift::Airlift(const Airlift& other) 
    : Order(other), 
      numUnits(other.numUnits), 
      sourceTerritory(other.sourceTerritory), 
      targetTerritory(other.targetTerritory), 
      hasAirliftCard(other.hasAirliftCard) {}


Airlift* Airlift::clone() const {
    return new Airlift(*this);
}

bool Airlift::validate() {
  return true;
}

/*
bool Airlift::validate() {
    if (!player->hasCard(AIRLIFT_CARD)) {
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


void Airlift::execute() {
    if (validate()) {
        // Move units from sourceTerritory to targetTerritory
        effect = "Airlifted " + std::to_string(numUnits) + " units from " + sourceTerritory + " to " + targetTerritory;
    }
}

std::ostream& operator<<(std::ostream& out, const Airlift& airlift) {
    out << "Order Type: " << airlift.description 
        << "\nUnits: " << airlift.numUnits 
        << "\nSource Territory: " << airlift.sourceTerritory 
        << "\nTarget Territory: " << airlift.targetTerritory 
        << "\nHas Airlift Card: " << (airlift.hasAirliftCard ? "Yes" : "No");
    if (!airlift.effect.empty()) {
        out << "\nEffect: " << airlift.effect;
    }
    return out;
}

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

Negotiate::Negotiate() : targetPlayer(""), hasDiplomacyCard(false) {
    description = "Negotiate Order";
}

Negotiate::Negotiate(const std::string target, bool hasCard) : targetPlayer(target), hasDiplomacyCard(hasCard) {
    description = "Negotiate Order";
}

Negotiate::Negotiate(const Negotiate& other) 
    : Order(other), 
      targetPlayer(other.targetPlayer), 
      hasDiplomacyCard(other.hasDiplomacyCard) {}


Negotiate* Negotiate::clone() const {
    return new Negotiate(*this);
}


bool Negotiate::validate() {
  return true;
}
/*
bool Negotiate::validate() {
    if (!player->hasCard(DIPLOMACY_CARD)) {
        return false;
    }
    if (targetPlayer == player) {
        return false;
    }
    return true;
}
*/

void Negotiate::execute() {
    if (validate()) {
        // Prevent attacks between current player and targetPlayer
        effect = "Negotiated with " + targetPlayer;
    }
}

std::ostream& operator<<(std::ostream& out, const Negotiate& negotiate) {
    out << "Order Type: " << negotiate.description 
        << "\nTarget Player: " << negotiate.targetPlayer 
        << "\nHas Diplomacy Card: " << (negotiate.hasDiplomacyCard ? "Yes" : "No");
    if (!negotiate.effect.empty()) {
        out << "\nEffect: " << negotiate.effect;
    }
    return out;
}

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

OrdersList::~OrdersList() {
    for (Order* order : orders) {
        delete order;
    }
    orders.clear();
}

void OrdersList::addOrder(Order* order) {
    orders.push_back(order);
}

void OrdersList::remove(Order* order) {
    orders.remove(order);
    delete order;
}


void OrdersList::move(Order* order, int position) {
    orders.remove(order);
    auto it = std::next(orders.begin(), position);
    orders.insert(it, order);
}



OrdersList::OrdersList(const OrdersList& other) {
    for (Order* order : other.orders) {
        orders.push_back(order->clone());
    }
}


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



std::ostream& operator<<(std::ostream& out, const OrdersList& ordersList) {
    out << "Orders List:" << std::endl;
    for (const Order* order : ordersList.orders) {
        out << *order << std::endl;
    }
    return out;
}
