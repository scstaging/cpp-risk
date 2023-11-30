#include <stdexcept>
#include <iostream>
#include <vector>
#include <algorithm>
#include "Player.h"
#include "Cards.h"
#include "PlayerStrategies.h"

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

// Extra constructor for ease of use when declaring computer players
Player::Player(std::string name, PlayerStrategy* strategy)
{
    this->playerName = new string(name);
    this->strategy = strategy;
    this->hand = new Hand();
    this->ordersList = new OrdersList();
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

int* Player::getReinforcementPool() const
{
    return this->reinforcementPool;
}

void Player::incrementReinforcementPool(int increase){
    this->reinforcementPool += increase;
}

vector<Continent*> Player::getContinents() const
{
    return this->continents;
}
 
vector<Territory*> Player::getTerritories() const
{
    return this->territories;
}

vector<Territory*> Player::getDefend() const
{
    return this->defend;
}

vector<Territory*> Player::getAttack() const
{
    return this->attack;
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

void Player::setStrategy(PlayerStrategy* strategy){
    this->strategy = strategy;
}

PlayerStrategy* Player::getStrategy()
{
    return this->strategy;
}

/* Mandatory Features For A1 */
bool Player::issueOrder(Deck* deck, Map* map, GameEngine *game)
{
    return this->getStrategy()->issueOrder(this, deck, map, game);
}

vector<Territory*> Player::toAttack() 
{
    return this->getStrategy()->toAttack(this);
}

vector<Territory*> Player::toDefend() 
{
    return this->getStrategy()->toDefend(this);
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
