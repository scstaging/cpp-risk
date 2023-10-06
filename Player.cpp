#include "Player.h"
#include "Cards.h"

#include <iostream>
#include <vector>

using std::istream;
using std::ostream;
using std::string;
using std::cout;

/* Default Constructor */
Player::Player()
{
    this->playerName = new string("New Player");
    this->hand = new Hand();
    // this->orders = new OrdersList();
    // this->territories = new Territory();
}

/* Constructor with name parameter */
Player::Player(string name)
{
    this->playerName = new string(name);
    this->hand = new Hand();
    // this->orders = new OrdersList();
    // this->territories = new Territory();
}

/* Copy Constructor */
Player::Player(const Player& copiedPlayer)
{
    this->playerName = new string(*copiedPlayer.playerName);
    this->hand = new Hand(*copiedPlayer.hand);
    // this->orders = copiedPlayer.orders;
    // this->territories = copiedPlayer.territories;
}

/* Destructor */
Player::~Player() 
{
    delete playerName;
    delete hand;
    // delete ordersList;
    // delete territories;
}

/* Operator Overloading */

/* Overloaded assignment operator */
Player& Player::operator=(const Player& player) 
{
    *this->playerName = *player.playerName;
    *this->hand = *player.hand; 
    // *this->orders = *player.orders;
    // *this->territories = *player.territories;
    
    return *this;
}

/* Overloaded input stream operator */
ostream& operator<<(ostream& output, const Player& player)
{
    output << "Player name: " << *player.playerName 
    << ",\nPlayer's hand: " << *player.hand
    << ",\nPlayer's orders list: " << " (replace with *player.ordersList)" 
    << ",\nPlayer's territories: " << "(replace with *player.territories)\n";

    return output;
}

/* Getters */
string* Player::getPlayerName() const 
{
    return this->playerName;
}

Hand* Player::getHand() const 
{
    return this->hand;
}

/* 
OrdersList* Player::getOrdersList() const 
{
    // return this->ordersList;
}
*/

/* 
vector<Territory*> Player::getTerritories() const
{
    return this->territories;
}
*/

/* Setters */
void Player::setPlayerName(string name) 
{
    *this->playerName = name;
}

void Player::setHand(Hand* hand) 
{
    *this->hand = *hand;
}
// 

/* 
void Player::setOrdersList(OrdersList* ordersList) 
{
    this->ordersList = ordersList;
}
*/

/* 
void Player::setTerritories(vector<Territory*> territories) 
{
    this->territories = territories;
}
*/

/* Mandatory Features For A1 */
void Player::issueOrder() 
{
    // create an order object and add it to the list of orders
    return;
}

/* 
vector<Territory*> Player::toAttack() 
{
    // return arbitrary (for now) list of territories that are to be attacked
}
*/

/*
vector<Territory*> Player::toAttack() 
{
    // return arbitrary (for now) list of territories that are to be attacked
}
*/
