#include "Orders.h"
// #include "Player.h"
// #include "Cards.h"
// #include "Map.h"

// Order class implementations

// Default constructor
Order::Order() : description(""), effect("") {}

// Destructor
Order::~Order() {}

// copy constructor
Order::Order(const Order &other) : description(other.description), effect(other.effect) {}

// Assignment operator of the base class order
Order &Order::operator=(const Order &other)
{
    if (this != &other)
    {
        description = other.description;
        effect = other.effect;
    }
    return *this;
}

// Print method useful for the stream insertion operator
void Order::print(std::ostream &out) const
{
    out << description;
    if (!effect.empty())
    {
        out << "  |  Effect: " << effect;
    }
}

// Stream insertion operator
std::ostream &operator<<(std::ostream &out, const Order &order)
{
    order.print(out);
    return out;
}

// Deploy class implementations

// Parameterized constructor

Deploy::Deploy(Player *player, std::string targetTerritoryName, GameEngine *game, int numOfArmies)
    : player(player), targetTerritoryName(targetTerritoryName), game(game), numOfArmies(numOfArmies), territory(nullptr)
{
    description = "Deploy Order";
}
// Destructor
Deploy::~Deploy() {}

// Copy constructor
Deploy::Deploy(const Deploy &other)
    : Order(other),
      player(other.player),
      targetTerritoryName(other.targetTerritoryName),
      game(other.game),
      numOfArmies(other.numOfArmies),
      territory(other.territory) {}

// Clone method
Deploy *Deploy::clone() const
{
    return new Deploy(*this);
}

// Print method useful for the stream insertion operator
void Deploy::print(std::ostream &out) const
{
    Order::print(out); // Call the superclass's print function
    out << "  |  Units: " << numOfArmies
        << "  |  Target Territory: " << targetTerritoryName;
}

// Stream insertion operator for deploy order
std::ostream &operator<<(std::ostream &out, const Deploy &deploy)
{
    deploy.print(out);
    return out;
}

// Assignment operator of the Deploy order
Deploy &Deploy::operator=(const Deploy &other)
{
    if (this != &other)
    {
        Order::operator=(other); // Call base class assignment operator
        player = other.player;
        targetTerritoryName = other.targetTerritoryName;
        game = other.game;
        numOfArmies = other.numOfArmies;
        territory = other.territory;
    }
    return *this;
}

bool Deploy::validate()
{
    territory = nullptr;
    // Get the vector of territories that the player owns.
    vector<Territory *> playerTerritories = player->getTerritories();
    // Find the territory by name within the player's territories.
    for (auto &t : playerTerritories)
    {
        if (t->getNameOfTerritory() == targetTerritoryName)
        {
            territory = t;
            break;
        }
    }
    if (territory)
    {
        if (player->getAvailableReinforcements() >= numOfArmies)
        {
            if (numOfArmies > 0)
            {
                std::cout << "Deployment validated." << std::endl;
                return true;
            }
            else
            {
                std::cout << "Deployment failed: enter a positive number of units." << std::endl;
            }
        }
        else
        {
            std::cout << "Deployment failed: Insufficient reinforcements." << std::endl;
        }
    }
    else
    {
        std::cout << "Deployment failed: Territory not found, or you do not own the territory." << std::endl;
    }

    return false;
}

// Player *player, int numberOfUnits, const std::string &targetTerritoryName
void Deploy::execute()
{
    if (validate())
    {
        // Increase the number of armies in the territory.
        *(territory->getNumArmies()) += numOfArmies;
        // Decrease the player's reinforcement pool.
        player->incrementReinforcementPool(-numOfArmies);
        // Store the result in 'effect'.
        effect = "Deployed " + std::to_string(numOfArmies) + " units to " + targetTerritoryName;
    }
}

// Advance class implementations

// Parameterized constructor
Advance::Advance(Player *player, std::string sourceTerritoryName, std::string targetTerritoryName, GameEngine *game, int units)
    : player(player), sourceTerritory(sourceTerritoryName), targetTerritory(targetTerritoryName), game(game), numUnits(units),
      srcTerritory(nullptr), trgtTerritory(nullptr)
{
    description = "Advance Order";
}

// Copy constructor
Advance::Advance(const Advance &other)
    : Order(other),
      player(other.player),
      game(other.game),
      numUnits(other.numUnits),
      sourceTerritory(other.sourceTerritory),
      targetTerritory(other.targetTerritory),
      srcTerritory(other.srcTerritory),
      trgtTerritory(other.trgtTerritory)
{
}

// Destructor
Advance::~Advance() {}

// Clone method
Advance *Advance::clone() const
{
    return new Advance(*this);
}

// Validate method
bool Advance::validate()
{
    srcTerritory = nullptr;
    trgtTerritory = nullptr;
    // Get the vector of territories that the player owns.
    vector<Territory *> playerTerritories = player->getTerritories();
    // check if the source territory belongs to the player's territories.
    for (auto &t : playerTerritories)
    {
        if (t->getNameOfTerritory() == sourceTerritory)
        {
            srcTerritory = t;
            break;
        }
    }
    bool isAdjacent = false;

    // check if the the target territory is adjacent to the source territory
    if (srcTerritory)
    {
        for (Territory *adjTerritory : srcTerritory->getAdjacentTerritory())
        {
            if (adjTerritory->getNameOfTerritory() == targetTerritory)
            {

                trgtTerritory = adjTerritory;
                isAdjacent = true;
                break;
            }
        }
    }
    else
    {
        std::cout << "Advance order invalid, the source territory does not belong to the player." << std::endl;
    }

    if (isAdjacent)
    {
        if (game->isUnderNegotiation(player, game->getOwnerOfTerritory(trgtTerritory)))
        {
            std::cout << "Advance order invalid due to ongoing negotiation." << std::endl;
            return false;
        }
        if (*srcTerritory->getNumArmies() >= numUnits)
        {
            if (numUnits > 0)
            {
                std::cout << "Advance order validated." << std::endl;
                return true;
            }
            else
            {
                std::cout << "Advance order failed: enter a positive number of units." << std::endl;
                return false;
            }
        }
        else
        {
            std::cout << "Advance order failed: Insufficient reinforcements." << std::endl;
            return false;
        }
    }
    else
    {
        std::cout << "Advance order invalid, the target territory is not adjacent to the source territory or does not exist." << std::endl;
        return false;
    }
}

// execute method
void Advance::execute()
{
    if (validate())
    {
        // check if the target territory belongs to the player issuing the advance order
        bool belongsToPlayer = false;
        vector<Territory *> playerTerritories = player->getTerritories();
        for (auto &t : playerTerritories)
        {
            if (t->getNameOfTerritory() == trgtTerritory->getNameOfTerritory())
            {
                belongsToPlayer = true;
                break;
            }
        }
        // If the target territory belongs to the player
        if (belongsToPlayer)
        {
            // transfering the units in the source territory to the target territory
            *(srcTerritory->getNumArmies()) -= numUnits;
            *(trgtTerritory->getNumArmies()) += numUnits;
            effect = "Advanced " + std::to_string(numUnits) + " units from " + sourceTerritory + " to " + targetTerritory +
                     ". Both the source and target territory belong to the player issuing the order.";
        }
        // if the target territory does not belong to the player
        else
        {
            // collecting the number of units in the target territory owned by another player
            int defendingUnits = *(trgtTerritory->getNumArmies());
            int advancedUnits = numUnits;

            while (advancedUnits > 0 && defendingUnits > 0)
            {
                // 60% chance for each attacking army to kill a defending army

                if ((rand() % 100) < 60)
                {
                    defendingUnits--;
                    if (defendingUnits == 0)
                    {
                        break;
                    }
                }
                // 70% chance for each defending army to kill an attacking army
                if ((rand() % 100) < 70)
                {
                    advancedUnits--;
                    if (advancedUnits == 0)
                    {
                        break;
                    }
                }
            }
            if (defendingUnits == 0)
            {
                // list of all players
                list<Player *> listOfPlayers = game->getPlayers();
                // find the player who owns the territory
                Player *defender = nullptr;

                // iterate through all the players
                for (Player *p : listOfPlayers)
                {
                    // iterate through all the territories owned by the player
                    vector<Territory *> playerTerritories = p->getTerritories();
                    for (Territory *t : playerTerritories)
                    {
                        if (t->getNameOfTerritory() == trgtTerritory->getNameOfTerritory())
                        {
                            defender = p;
                            break;
                        }
                    }
                    if (defender)
                    {
                        break;
                    }
                }
                if (defender)
                {
                    // Get the list of territories, make changes, and then set it back
                    vector<Territory *> defenderTerritories = defender->getTerritories();
                    vector<Territory *> attackerTerritories = player->getTerritories();

                    // Remove territory from defender
                    auto it = std::remove(defenderTerritories.begin(), defenderTerritories.end(), trgtTerritory);
                    if (it != defenderTerritories.end())
                    {
                        defenderTerritories.erase(it);
                        defender->setTerritories(defenderTerritories);
                    }

                    // Add territory to attacker
                    attackerTerritories.push_back(trgtTerritory);
                    player->setTerritories(attackerTerritories);

                    // Updating the units
                    *(trgtTerritory->getNumArmies()) = advancedUnits;
                    *(srcTerritory->getNumArmies()) -= numUnits;
                    effect = "Advanced " + std::to_string(numUnits) + " units from " + sourceTerritory + " to " + targetTerritory +
                             ". The attacker captured the territory and there are  " + std::to_string(advancedUnits) + " that survived.";
                }
                else
                {

                    std::cout << "Could not find the defending player." << std::endl;
                }
            }
            else if (advancedUnits == 0)
            {
                // Updating the units
                *(srcTerritory->getNumArmies()) -= numUnits;
                effect = "All the " + std::to_string(numUnits) + " units that advanced died, therefore the attacker did not manage to capture the territory";
            }
        }
    }
}

// Print method useful for the stream insertion operator
void Advance::print(std::ostream &out) const
{
    Order::print(out);
    out << "  |  Units: " << numUnits
        << "  |  Source Territory: " << sourceTerritory
        << "  |  Target Territory: " << targetTerritory;
}

// Stream insertion operator for advance order
std::ostream &operator<<(std::ostream &out, const Advance &advance)
{
    advance.print(out);
    return out;
}

// Assignment operator of the advance order
Advance &Advance::operator=(const Advance &other)
{
    if (this != &other)
    {
        Order::operator=(other);
        // Copy all members
        player = other.player;
        game = other.game;
        numUnits = other.numUnits;
        sourceTerritory = other.sourceTerritory;
        targetTerritory = other.targetTerritory;
        srcTerritory = other.srcTerritory;
        trgtTerritory = other.trgtTerritory;
    }
    return *this;
}

// Bomb class implementations

// Parameterized constructor for Bomb class
Bomb::Bomb(Player *player, std::string targetTerritoryName, GameEngine *game, Map *map)
    : player(player), targetTerritory(targetTerritoryName), game(game), map(map), trgtTerritory(nullptr)
{
    description = "Bomb Order";
}

// Copy constructor
Bomb::Bomb(const Bomb &other)
    : Order(other), // Calling the base class copy constructor
      targetTerritory(other.targetTerritory),
      trgtTerritory(other.trgtTerritory),
      map(other.map),
      player(other.player),
      game(other.game)
{
}

// Destructor
Bomb::~Bomb() {}

// Clone method
Bomb *Bomb::clone() const
{
    return new Bomb(*this);
}

// Validate method
bool Bomb::validate()
{
    trgtTerritory = nullptr;

    /*
    if (!player->hasCard(CardType::bomb))
    {
        std::cout << "Bomb order failed: the player issuing the order does not have the bomb card." << std::endl;
        return false;
    }
    */

    // check if the target territory belongs to the player's territories.
    for (Territory *territory : player->getTerritories())
    {
        if (territory->getNameOfTerritory() == targetTerritory)
        {
            std::cout << "Bomb order failed: the target territory belongs to the player issuing the order." << std::endl;
            return false;
        }
    }
    // find the target territory pointer
    vector<Territory *> allTerritories = map->getTerritory();
    for (Territory *territory : allTerritories)
    {
        if (territory->getNameOfTerritory() == targetTerritory)
        {
            trgtTerritory = territory;
            break;
        }
    }
    bool isAdjacent = false;

    if (trgtTerritory)
    {
        // check if the target territory is adjacent to any of the territories owned by the player
        for (Territory *adjTerritory : trgtTerritory->getAdjacentTerritory())
        {
            for (Territory *ownedTerritories : player->getTerritories())
            {
                if (ownedTerritories->getNameOfTerritory() == adjTerritory->getNameOfTerritory())
                {
                    isAdjacent = true;
                    break;
                }
            }
            if (isAdjacent)
            {
                break;
            }
        }
        if (isAdjacent)
        {
            std::cout << "Bomb order validated." << std::endl;
            return true;
        }
        else
        {
            std::cout << "Bomb order failed: the target territory is not adjacent to any of the territories owned by the player issuing the order." << std::endl;
            return false;
        }
    }
    else
    {
        std::cout << "Bomb order failed: the target territory does not exist." << std::endl;
        return false;
    }
}

void Bomb::execute()
{
    if (validate())
    {
        *(trgtTerritory->getNumArmies()) /= 2;
        // Halve the units on targetTerritory
        effect = "Bombed " + targetTerritory;
    }
}

// Print method useful for the stream insertion operator
void Bomb::print(std::ostream &out) const
{
    Order::print(out);
    out << "  |  Target Territory: " << targetTerritory;
}

// Stream insertion operator for bomb order
std::ostream &operator<<(std::ostream &out, const Bomb &bomb)
{
    bomb.print(out);
    return out;
}

// Assignment operator of the bomb order
Bomb &Bomb::operator=(const Bomb &other)
{
    if (this != &other)
    {
        Order::operator=(other); // Call base class assignment operator
        this->player = other.player;
        this->game = other.game;
        this->map = other.map;
        this->targetTerritory = other.targetTerritory;
        this->trgtTerritory = other.trgtTerritory;
    }
    return *this;
}

// Blockade class implementations

// Parameterized constructor
Blockade::Blockade(Player *player, std::string targetTerritoryName, GameEngine *game)
    : player(player), targetTerritory(targetTerritoryName), game(game), trgtTerritory(nullptr)
{
    description = "Blockade Order";
}

// Copy constructor
Blockade::Blockade(const Blockade &other)
    : Order(other),
      player(other.player),
      targetTerritory(other.targetTerritory),
      game(other.game),
      trgtTerritory(other.trgtTerritory) {}

// Destructor
Blockade::~Blockade() {}

// Clone method
Blockade *Blockade::clone() const
{
    return new Blockade(*this);
}

// Validate method
bool Blockade::validate()
{
    trgtTerritory = nullptr;

    /*
    Check if player has the blockade card
    if (!player->hasCard(CardType::blockade))
    {
        std::cout << "Blockade order failed: the player does not have a blockade card." << std::endl;
        return false;
    }
    */
    // Check if the target territory belongs to the player
    for (Territory *territory : player->getTerritories())
    {
        if (territory->getNameOfTerritory() == targetTerritory)
        {
            std::cout << "Blockade order validated." << std::endl;
            this->trgtTerritory = territory;
            return true;
        }
    }
    std::cout << "Blockade order failed: the target territory does not belong to the player." << std::endl;
    return false;
}

void Blockade::execute()
{
    if (validate())
    {
        /*
        if (neutralPlayer == nullptr)
        {
            neutralPlayer = new Player("Neutral Player");
            // Add neutralPlayer to the game's list of players
            // game->addPlayer(neutralPlayer);
        }

         // Add the territory to the list of the neutral player
        vector<Territory *> neutralPlayerTerritories = neutralPlayer->getTerritories();
        neutralPlayerTerritories.push_back(trgtTerritory);
        neutralPlayer->setTerritories(neutralPlayerTerritories);
        */

        // Double the units on targetTerritory
        *(trgtTerritory->getNumArmies()) *= 2;
        // Remove the territory from the list of owned territories by the owner
        vector<Territory *> currentPlayerTerritories = player->getTerritories();
        currentPlayerTerritories.erase(remove(currentPlayerTerritories.begin(), currentPlayerTerritories.end(), trgtTerritory),
                                       currentPlayerTerritories.end());
        player->setTerritories(currentPlayerTerritories);

        effect = "Blockade executed on " + targetTerritory;
    }
}

// Print method useful for the stream insertion operator
void Blockade::print(std::ostream &out) const
{
    Order::print(out);
    out << "  |  Target Territory: " << targetTerritory;
}

// Stream insertion operator for blockade order
std::ostream &operator<<(std::ostream &out, const Blockade &blockade)
{
    blockade.print(out);
    return out;
}

// Assignment operator of the blockade order

Blockade &Blockade::operator=(const Blockade &other)
{
    if (this != &other)
    {
        Order::operator=(other);
        player = other.player;
        targetTerritory = other.targetTerritory;
        game = other.game;
        trgtTerritory = other.trgtTerritory;
    }
    return *this;
}
// Airlift class implementations

// Parameterized constructor
Airlift::Airlift(Player *player, std::string sourceTerritoryName, std::string targetTerritoryName, GameEngine *game, int units)
    : player(player), sourceTerritory(sourceTerritoryName), targetTerritory(targetTerritoryName), game(game), numUnits(units),
      srcTerritory(nullptr), trgtTerritory(nullptr)
{
    description = "Airlift Order";
}

// Copy constructor
Airlift::Airlift(const Airlift &other)
    : Order(other),
      player(other.player),
      game(other.game),
      srcTerritory(other.srcTerritory),
      trgtTerritory(other.trgtTerritory),
      numUnits(other.numUnits),
      sourceTerritory(other.sourceTerritory),
      targetTerritory(other.targetTerritory) {}

// Destructor
Airlift::~Airlift() {}

// Clone method
Airlift *Airlift::clone() const
{
    return new Airlift(*this);
}

// Validate method
bool Airlift::validate()
{
    srcTerritory = nullptr;
    trgtTerritory = nullptr;
    /*
    if (!player->hasCard(CardType::airlift))
    {
        std::cout << "Airlift Order invalid, the player does not have the airlift card." << std::endl;
        return false;
    }
    */

    // Get the vector of territories that the player owns.
    // vector<Territory *> playerTerritories = player->getTerritories();
    // check if the source and target territory belongs to the player's territories.
    bool sourceOwned = false;
    bool targetOwned = false;
    for (Territory *territory : player->getTerritories())
    {
        if (territory->getNameOfTerritory() == sourceTerritory)
        {
            srcTerritory = territory;
            sourceOwned = true;
        }
        if (territory->getNameOfTerritory() == targetTerritory)
        {
            trgtTerritory = territory;
            targetOwned = true;
        }
    }
    if (!targetOwned)
    {
        std::cout << "Airlift Order invalid, the player does not own the target territory." << std::endl;
        return false;
    }
    if (!sourceOwned)
    {
        std::cout << "Airlift Order invalid, the player does not own the source territory." << std::endl;
        return false;
    }
    if (srcTerritory == trgtTerritory)
    {
        std::cout << "Airlift Order invalid: Source and target territories cannot be the same." << std::endl;
        return false;
    }
    if (*srcTerritory->getNumArmies() >= numUnits)
    {
        if (numUnits > 0)
        {
            std::cout << "Airlift order validated." << std::endl;
            return true;
        }
        else
        {
            std::cout << "Airlift order failed: enter a positive number of units." << std::endl;
            return false;
        }
    }
    else
    {
        std::cout << "Airlift order failed: Insufficient reinforcements." << std::endl;
        return false;
    }
}

// Execute method
void Airlift::execute()
{
    if (validate())
    {
        // Move units from sourceTerritory to targetTerritory
        *(srcTerritory->getNumArmies()) -= numUnits;
        *(trgtTerritory->getNumArmies()) += numUnits;
        effect = "Airlifted " + std::to_string(numUnits) + " units from " + sourceTerritory + " to " + targetTerritory;
    }
}

// Print method useful for the stream insertion operator
void Airlift::print(std::ostream &out) const
{
    Order::print(out);
    out << "  |  Units: " << numUnits
        << "  |  Source Territory: " << sourceTerritory
        << "  |  Target Territory: " << targetTerritory;
}

// Stream insertion operator for airlift order
std::ostream &operator<<(std::ostream &out, const Airlift &airlift)
{
    airlift.print(out);
    return out;
}

// Assignment operator of the airlift order
Airlift &Airlift::operator=(const Airlift &other)
{
    if (this != &other)
    {

        Order::operator=(other);
        player = other.player;
        game = other.game;
        numUnits = other.numUnits;
        sourceTerritory = other.sourceTerritory;
        targetTerritory = other.targetTerritory;
        srcTerritory = other.srcTerritory;
        trgtTerritory = other.trgtTerritory;
    }
    return *this;
}

// Negotiate class implementations

// Default constructor

// Parameterized constructor
Negotiate::Negotiate(Player *player, Player *targetPlayer, GameEngine *game) : player(player), targetPlayer(targetPlayer), game(game)
{
    description = "Negotiate Order";
}

// Copy constructor
Negotiate::Negotiate(const Negotiate &other)
    : Order(other),
      player(other.player),
      targetPlayer(other.targetPlayer),
      game(other.game) {}

// Destructor
Negotiate::~Negotiate() {}

// Clone method
Negotiate *Negotiate::clone() const
{
    return new Negotiate(*this);
}

// Validate method
bool Negotiate::validate()
{
    // Check if the player and the target player are not the same
    if (player == targetPlayer)
    {
        std::cout << "Negociate order failed: Player cannot target himself." << std::endl;
        return false;
    }
    return true;
}

void Negotiate::execute()
{

    if (validate())
    {
        game->addNegotiation(player, targetPlayer);
        // then the effect is that any attack that may be declared between territories
        // of the player issuing the negotiate order and the target player will result in an invalid order.
        effect = "Player named " + *(player->getPlayerName()) + " negotiated with " + *(targetPlayer->getPlayerName()) + " for the remainder of the turn.";
    }
}

// Print method useful for the stream insertion operator
void Negotiate::print(std::ostream &out) const
{
    Order::print(out);
    out << "  |  Target Player: " << targetPlayer->getPlayerName();
}

// Stream insertion operator for negotiate order
std::ostream &operator<<(std::ostream &out, const Negotiate &negotiate)
{
    negotiate.print(out);
    return out;
}

// Assignment operator of the negotiate order
Negotiate &Negotiate::operator=(const Negotiate &other)
{
    if (this != &other)
    {
        Order::operator=(other);
        targetPlayer = other.targetPlayer;
        player = other.player;
        game = other.game;
    }
    return *this;
}

// OrdersList class implementations
OrdersList::OrdersList() {}

// Destructor of the orders list
OrdersList::~OrdersList()
{
    for (Order *order : orders)
    {
        delete order;
    }
    orders.clear();
}

// Getter method to return the pointer to an order inside the list
const std::list<Order *> &OrdersList::getOrders() const
{
    return orders;
}

// Method to add orders inside the list
void OrdersList::addOrder(Order *order)
{
    orders.push_back(order);
}

void OrdersList::remove(int index)
{
    if (index < 0 || index >= orders.size())
    {
        std::cerr << "Invalid index provided for removal operation." << std::endl;
        return;
    }
    std::list<Order *>::iterator it = std::next(orders.begin(), index);
    delete *it;
    orders.erase(it);
}

void OrdersList::move(int sourceIndex, int targetIndex)
{
    // Check if the indices are valid
    if (sourceIndex < 0 || sourceIndex >= orders.size() || targetIndex < 0 || targetIndex > orders.size())
    {
        std::cerr << "Invalid indices provided for move operation." << std::endl;
        return;
    }

    // Get the order at the source index
    std::list<Order *>::iterator sourceIt = std::next(orders.begin(), sourceIndex);
    Order *orderToMove = *sourceIt;

    // Remove the order from the list (without deleting it)
    orders.erase(sourceIt);

    // Insert the order at the target index
    std::list<Order *>::iterator targetIt = std::next(orders.begin(), targetIndex);
    orders.insert(targetIt, orderToMove);
}

// Copy constructor for the orders list
OrdersList::OrdersList(const OrdersList &other)
{
    for (Order *order : other.orders)
    {
        orders.push_back(order->clone());
    }
}

// Assignment operator for the orders list
OrdersList &OrdersList::operator=(const OrdersList &other)
{
    if (this != &other)
    {
        // First, delete the existing orders in the current object
        for (Order *order : orders)
        {
            delete order;
        }
        orders.clear();

        // Now, copy orders from the other OrdersList using the clone method
        for (Order *order : other.orders)
        {
            orders.push_back(order->clone());
        }
    }
    return *this;
}

// Stream insertion operator for the orders list
std::ostream &operator<<(std::ostream &out, const OrdersList &ordersList)
{
    out << "Orders List:" << std::endl;
    for (const Order *order : ordersList.orders)
    {
        out << *order << std::endl;
    }
    return out;
}
