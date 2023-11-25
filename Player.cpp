#include "Player.h"
#include "Cards.h"
#include <stdexcept>
#include <iostream>
#include <vector>
#include <algorithm>

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


/* Mandatory Features For A1 */
bool Player::issueOrder(Deck* deck, Map* map, GameEngine *game)
{
    
    if(*this->reinforcementPool > 0){
        cout << this->playerName << ", it is your turn to issue an order. You still have reinforcements that must be deployed." << endl;
        cout << "Which territory would you like to deploy them in?" << endl;
        int counter = 0;

        for(Territory* t : toDefend()){
            cout << counter << ": " << t->getNameOfTerritory() << endl;
            counter++;
        }

        int userTerritoryChoice;
        cout << "Enter the number of the territory you would like to choose: ";
        cin >> userTerritoryChoice;


        Territory* territory = nullptr;

        if(userTerritoryChoice >= 0 && userTerritoryChoice < toDefend().size()){    
            territory = this->defend[userTerritoryChoice];
        }
        else{
            cout << "Invalid choice. Please try again." << endl;
        }

        string deployedTerritoryName = territory->getNameOfTerritory();

        int userTroopChoice;
        cout << "How many troops would you like to deploy? You have " << this->reinforcementPool << " remaining in your reinforcement pool." << endl; 
        
        while(userTroopChoice > 0 && userTroopChoice <= *this->reinforcementPool)
            cin >> userTroopChoice;
        
	Deploy *deploy = new Deploy(this, deployedTerritoryName, userTroopChoice); // Updated to match the new Deploy constructor
	    

        this->ordersList->addOrder(deploy);

        cout << "Troops deployed." << endl;

        this->reinforcementPool -= userTroopChoice;
    }
    else{
        cout << this->playerName << ", it is your turn to issue an order. What would you like to do?" << endl;
        int userChoice;

        list<int> options = list<int>(); 
        
        cout << "1. Advance" << endl;
        options.push_back(1);

        if(this->hand->getCardsInHand()->size() > 0){
            cout << "2. Play a card" << endl;
            options.push_back(2);
        }

        cout << "3. End your turn" << endl;
        options.push_back(3);

        while (find_if(options.begin(), options.end(),
            [userChoice](const auto& option) { return option == userChoice; }) != options.end()) {
            cin >> userChoice;
        }

        switch(userChoice){
            // Advance
            case 1:{
                cout << "Select your troops from which territory?" << endl;
                int counter = 0; 
                
                for(Territory* t : toDefend()){
                    cout << counter << ": " << t->getNameOfTerritory() << endl;
                    counter++;
                }

                int sourceTerritoryNumber;
                cout << "Enter the number of the territory you would like to choose: ";
                cin >> sourceTerritoryNumber;

                Territory* sourceTerritory = nullptr;

                if(sourceTerritoryNumber >= 0 && sourceTerritoryNumber < toDefend().size()){    
                    sourceTerritory = this->defend[sourceTerritoryNumber];
                }
                else{
                    cout << "Invalid choice. Please try again." << endl;
                }

                cout << "How many troops would you like to move? There are " << sourceTerritory->getNumArmies() << " troops in this territory." << endl;

                int troopNumber;
                while(troopNumber > 0 && troopNumber <= *sourceTerritory->getNumArmies()){
                    cin >> troopNumber;
                }

                cout << "Which territory would you like to advance your targets to?" << endl;

                vector<Territory*> combinedAttackDefend;
                int counter2 = 0;

                cout << "Territories you can attack: " << endl;
                for(Territory* t : this->toAttack()){
                    combinedAttackDefend.push_back(t);
                    cout << counter2 << ": " << t->getNameOfTerritory() << endl;
                    counter2++;
                }

                cout << "\n";

                cout << "Territories you can defend: " << endl;
                for(Territory* t : this->toDefend()){
                    combinedAttackDefend.push_back(t);
                    cout << counter2 << ": " << t->getNameOfTerritory() << endl;
                    counter2++;
                }

                int targetTerritoryNumber;
                cout << "Enter the number of the territory you would like to choose: ";
                cin >> targetTerritoryNumber;

                Territory* targetTerritory = nullptr;

                if(targetTerritoryNumber >= 0 && targetTerritoryNumber < combinedAttackDefend.size()){
                    targetTerritory = combinedAttackDefend[targetTerritoryNumber];
                }
                else{
                    cout << "Invalid choice. Please try again.";
                }

		Advance *advanceOrder = new Advance(this, sourceTerritory->getNameOfTerritory(), targetTerritory->getNameOfTerritory(), game, troopNumber);

                this->ordersList->addOrder(advanceOrder);

                cout << "Advance order made." << endl;
                break;
            }
            // Card
            case 2:{

                cout << "Which card would you like to play?" << endl;
                int counter = 0; 

                auto& cardReference = *this->hand->getCardsInHand();


		vector<Card *> cards;
            	for (Card &card : cardReference)
            	{
                	cards.push_back(&card);
            	}

                for(Card* c : cards){
                    cout << counter << ": " << c->cardTypeToString(c->getType()) << endl;
                    counter++;
                }

                int userCardChoice;
                cout << "Enter the number of the card you would like to play: ";
                cin >> userCardChoice;

                Card* userCard = nullptr;

                if(userCardChoice > 0 && userCardChoice < cards.size()){
                    userCard = cards[userCardChoice];
                }

                cout << "Playing the " << userCard->cardTypeToString(userCard->getType()) << " card." << endl;

                userCard->play(deck, hand);

                break;
            }
            case 3:{
                cout << "Ending your turn." << endl;
                return false;
            }
            default:{
                //throw exception("Invalid choice. Please try again.");
		throw std::runtime_error("Invalid choice. Please try again.");
            }
        }
    }
    return true;
}


vector<Territory*> Player::toAttack() 
{
    // return arbitrary (for now) list of territories that are to be attacked
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
