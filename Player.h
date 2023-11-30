#pragma once
#include "Cards.h"
#include "Orders.h"
#include "Map.h"
#include "PlayerStrategies.h"

#include <vector>
#include <string>

using std::istream;
using std::ostream;
using std::string;

// forward declaration of classes
class OrdersList;
class Map;
class Territory;
class GameEngine;
class PlayerStrategy;
class Continent;

class Player {
    public:
        Player();   
        Player(string name);
        Player(string name, PlayerStrategy* strategy);   
        Player(const Player& player);
        ~Player();

        /* Operator Overloading */
        Player& operator=(const Player& player);
        friend ostream& operator<<(ostream& output, const Player& player);

        /* Getters */
        string* getPlayerName() const;
        Hand* getHand() const;
        OrdersList* getOrdersList() const;
        int* getReinforcementPool() const; 
        void incrementReinforcementPool(int increase); 
        vector<Continent*> getContinents() const;
        vector<Territory*> getTerritories() const;
        vector<Territory*> getDefend() const;
        vector<Territory*> getAttack() const;
        PlayerStrategy* getStrategy();

        /* Setters */
        void setPlayerName(string name);
        void setHand(Hand* hand);
        void setTerritories(vector<Territory*> territories);
        void setStrategy(PlayerStrategy *strategy);

        /* Mandatory Features For A1 */
        bool issueOrder(Player* player, Deck* deck, Map* map, GameEngine *game); // creates an Order object and puts it in the player’s list of orders
        vector<Territory*> toAttack(); // returns a list of territories that are to be attacked (for now, arbitrary list)
        vector<Territory*> toDefend(); // returns a list of territories that are to be defended (for now, arbitrary list)
        
        /* Additional features */
        bool hasCard(CardType);
        int getAvailableReinforcements();
        
    private:
        string* playerName;
        Hand* hand;
        OrdersList* ordersList;
        int* reinforcementPool; 
        vector<Continent*> continents;
        vector<Territory*> territories;
        vector<Territory*> attack;
        vector<Territory*> defend;
        PlayerStrategy* strategy;
};
