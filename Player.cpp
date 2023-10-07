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
    this->ordersList = new OrdersList();
    // this->territories = new Territory();
}

/* Constructor with name parameter */
Player::Player(string name)
{
    this->playerName = new string(name);
    this->hand = new Hand();
    this->ordersList = new OrdersList();
    // this->territories = new Territory();
}

/* Copy Constructor */
Player::Player(const Player& copiedPlayer)
{   
    this->playerName = new string(*copiedPlayer.playerName);
    this->hand = new Hand(*copiedPlayer.hand);
    this->ordersList = new OrdersList(*copiedPlayer.ordersList);
    // this->territories = copiedPlayer.territories;
}

/* Destructor */
Player::~Player() 
{
    delete playerName;
    delete hand;
    delete ordersList;
    // delete territories;
}

/* Operator Overloading */

/* Overloaded assignment operator */
Player& Player::operator=(const Player& player) 
{
    *this->playerName = *player.playerName;
    *this->hand = *player.hand; 
    // *this->ordersList = *player.ordersList;
    // *this->territories = *player.territories;
    
    return *this;
}

/* Overloaded input stream operator */
ostream& operator<<(ostream& output, const Player& player)
{
    output << "Player name: " << *player.playerName 
    << ",\nPlayer's hand: " << *player.hand
    << ",\nPlayer's orders list: " << *player.ordersList 
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


OrdersList* Player::getOrdersList() const 
{
    return this->ordersList;
}


 
vector<Territory*> Player::getTerritories() const
{
    return this->territories;
}


/* Setters */
void Player::setPlayerName(string name) 
{
    *this->playerName = name;
}

void Player::setHand(Hand* hand) 
{
    *this->hand = *hand;
}


void Player::setTerritories(vector<Territory*> territories) 
{
    this->territories = territories;

    int size = this->territories.size();

    unsigned int offset = int(size/10);
    unsigned int offset_2 = 2 * offset;

    cout << "offset: " << offset;

    vector<Territory*> toAttack = vector<Territory*>(this->territories.begin(), this->territories.begin()+offset);
    vector<Territory*> toDefend = vector<Territory*>(this->territories.begin()+offset, this->territories.begin()+offset_2);

    this->attack = toAttack;
    this->defend = toDefend;
}


/* Mandatory Features For A1 */
void Player::issueOrder()
{
    // for now: adds some arbitrary orders to the player's orderlist
    // eventual functionality: creates an order object and add it to the list of orders
    this->ordersList->addOrder(new Deploy());
    this->ordersList->addOrder(new Bomb());
    this->ordersList->addOrder(new Blockade());
    return;
}


vector<Territory*> Player::toAttack() 
{
    // return arbitrary (for now) list of territories that are to be attacked
    cout << "To attack:\n";
    for (unsigned int i = 0; i < this->attack.size(); i++) {
        cout << this->attack[i]->getNameOfTerritory() << "\n";
    }

    return this->attack;
}



vector<Territory*> Player::toDefend() 
{
    // return arbitrary (for now) list of territories that are to be defended
    cout << "To defend:\n";
    for (unsigned int i = 0; i < this->defend.size(); i++) {
        cout << this->defend[i]->getNameOfTerritory() << "\n";
    }

    return this->defend;
}


/* Additional Features */
bool Player::hasCard(CardType type) {
    for (Card& card : *this->getHand()->getCardsInHand()) {
		if (card.getType() == type) {
            return true;
        }
	}
    return false;
}

int Player::getAvailableReinforcements() {
    int available = 0;
    
    for (Card& card : *this->getHand()->getCardsInHand()) {
		if (card.getType() == CardType::reinforcement) {
            available++;
        }
	}
    return available;
}
