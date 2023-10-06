#pragma once
#include "Cards.h"
// #include "Orders.h"
// #include "Map.h"

#include <vector>
#include <string>

using std::istream;
using std::ostream;
using std::string;

class Player {
    public:
        Player();   
        Player(string name);   
        Player(const Player& player);
        ~Player();

        /* Operator Overloading */
        Player& operator=(const Player& player);
        friend ostream& operator<<(ostream& output, const Player& player);

        /* Getters */
        string* getPlayerName() const;
        Hand* getHand() const;
        // OrdersList* getOrdersList() const;
        // vector<Territory*> getTerritories() const;

        /* Setters */
        void setPlayerName(string name);
        void setHand(Hand* hand);
        // void setOrdersList(OrdersList* ordersList);
        // void setTerritories(vector<Territory*> territories);

        /* Mandatory Features For A1 */
        void issueOrder(); // creates an Order object and puts it in the player’s list of orders
        // vector<Territory*> toAttack(); // returns a list of territories that are to be attacked (for now, arbitrary list)
        // vector<Territory*> toDefend(); // returns a list of territories that are to be defended (for now, arbitrary list)

    private:
        string* playerName;
        Hand* hand;
        // OrdersList* ordersList;
        // vector<Territory*> territories;
};

void testPlayers();
