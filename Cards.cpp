#include <iostream>
using namespace std;

#include "Cards.h"

//Card class


// Default constructor for Card class.
Card::Card() {
	//  Card will default to type bomb. 
    type = new CardType(bomb);
}

// Specialized constructor for Card class.
Card::Card(CardType spectype){
    type = new CardType(spectype);
}

// Copy constructor for Card class. 
Card::Card(const Card &copycard) {
	type = new CardType(*copycard.type);
}

// Deconstructor for Card class. 
Card::~Card() {
	delete this->type;
	this->type = nullptr;
}

// Play method for Card class. Will allow the player
// to play the current card in their hand. 
void Card::play(Deck* deck, Hand* hand) {
	CardType type = *this->type;

	switch (type) {
		case bomb:
		{
			cout << "This is a card of type Bomb. \n";
			break;
		}
		case reinforcement:
		{
			cout << "This is a card of type Reinforcement. \n";
			break;
		}
		case blockade:
		{
			cout << "This is a card of type Blockade. \n";
			break;
		}
		case airlift:
		{
			cout << "This is a card of type Airlift. \n";
			break;
		}
		case diplomacy:
		{
			cout << "This is a card of type Diplomacy. \n";
			break;
		}
		default:
		{
			cout << "Invalid card type. \n";
			break;
		}

	}

	//Removes card from player's hand
	hand->removeCard(type);

	//Places the card back into the deck
	deck->addCard(type);
}

// Returns the type of the current card. 
CardType Card::getType() const {
    return *this->type;
}

// Sets the type of the current card to a specified type. 
void Card::setType(CardType* newType){
    *this->type = *newType;
}

// Returns the type of a card as a string.
string Card::cardTypeToString(CardType type) const {
    switch(type){
        case CardType::airlift:
            return "airlift";
        case CardType::blockade:
            return "blockade";
        case CardType::bomb:
            return "bomb";
        case CardType::reinforcement:
            return "reinforcement";
        case CardType::diplomacy:
            return "diplomacy";
        default:
            return "Unknown";            
    }
}

// Overloaded assignment operator
Card& Card::operator=(const Card& card) {
	*this->type = *card.type;

	return *this;
}

// Overloaded stream insertion operator
std::ostream& operator<<(std::ostream& output, const Card& card) {
	output << card.cardTypeToString(card.getType()) << "\n";

	return output;
}

// Overloaded stream extraction operator
std::istream& operator>>(std::istream& input, Card& card) {

	return input;
}

// Deck class

// Default constructor for Deck class.
Deck::Deck() {
	list <Card>* cardList = new list<Card>();

	//Defaults the number cards to 3 each.
	for (int i = 0; i < 3; i++) {
		cardList->push_back(*new Card(bomb));
		cardList->push_back(*new Card(reinforcement));
		cardList->push_back(*new Card(blockade));
		cardList->push_back(*new Card(airlift));
		cardList->push_back(*new Card(diplomacy));
	}	
	// Sets the deckCards variable to the function member "cardList"
	this->deckCards = cardList;
}

// Specialized constructor for Deck class.
Deck::Deck(int numCards) {
	
	list <Card>* cardList = new list<Card>();

	for (int i = 0; i < numCards; i++) {
		cardList->push_back(*new Card(bomb));
		cardList->push_back(*new Card(reinforcement));
		cardList->push_back(*new Card(blockade));
		cardList->push_back(*new Card(airlift));
		cardList->push_back(*new Card(diplomacy));
	}

	this->deckCards = cardList;
}

// Copy constructor for deck class
Deck::Deck(Deck &copydeck) {
	list<Card>* newDeck = new list<Card>(copydeck.deckCards->begin(), copydeck.deckCards->end());
	this->deckCards = newDeck;
}

Deck::~Deck() {
	delete this->deckCards;
	deckCards = nullptr;
}

// Draw method for Deck class. Will allow the player to draw a card
// from the Deck list and place it in their hand. 
string Deck::draw(Hand* hand) {
	if (this->deckCards->size() == 0) {
		return "No cards found in the deck.";
	}

	srand(static_cast<unsigned int>(time(nullptr)));

	int randomIndex = rand() % this->deckCards->size(); 

	list<Card>::iterator it = this->deckCards->begin();

	advance(it, randomIndex); 
	
	//Adds the card to the players hand
	hand->addCard(*it);
 
	//Erases the card from the deck. 
	deckCards->erase(it);

	return "Cards found and erased.";
}

// Adds a card of a specific type to the deck.
void Deck::addCard(CardType type) {
	Card* newCard = new Card(type);
	deckCards->push_back(*newCard);
}

// Returns the size of the deck. 
int Deck::getDeckSize() const {
	return deckCards->size();
}

// Overloaded assignment operator
Deck& Deck::operator=(const Deck& deck) {
	delete this->deckCards;
	
	this->deckCards = new list<Card>(deck.deckCards->begin(), deck.deckCards->end());;

	return *this;
}

// Overloaded stream insertion operator
std::ostream& operator<<(std::ostream& output, const Deck& deck) {
	output << "Deck has " << deck.getDeckSize() << " cards.\n";

	return output;
}

// Overloaded stream extraction operator
istream& operator>>(istream& input, const Deck& deck){
	Card incard;
	input >> incard;
	deck.deckCards->push_back(incard);

	return input;
}

// Hand class

// Default constructor for Hand class. 
Hand::Hand() {
	this->cardsInHand = new list<Card>();
}

// Copy constructor for Hand class.
Hand::Hand(Hand &copyhand){
	list<Card>* newHand = new list<Card>(copyhand.cardsInHand->begin(), copyhand.cardsInHand->end());
	this->cardsInHand = newHand;
}

// Deconstructor for Hand Class. 
Hand::~Hand() {
	delete this->cardsInHand;
	this->cardsInHand = nullptr;
}

// Adds a card of a specific type to the player's hand.
void Hand::addCard(CardType& type) {
	Card* newCard = new Card(type);
	cardsInHand->push_back(*newCard);
}

void Hand::addCard(Card& card){
	this->cardsInHand->push_back(card);
}

// Removes the first card of a specific type from the player's hand. 
void Hand::removeCard(CardType& type) {
	list<Card>::iterator it;

	for (it = cardsInHand->begin(); it != cardsInHand->end(); ++it) {
		if (it->getType() == type) {
			cardsInHand->erase(it);
			return;
		}
	}
}

// Returns the type of each card in the player's hand. 
string Hand::getCards() const {
	cout << "This hand has the following cards:\n";

	string *result = new string("");

	for (Card& card : *cardsInHand) {
		*result += card.cardTypeToString(card.getType()) + " ";
	}

	*result += "\n";

	return *result;
}

list<Card>* Hand::getCardsInHand() const {
	return this->cardsInHand;
}

// Overloaded assignment operator
Hand& Hand::operator=(const Hand& hand) {
	delete this->cardsInHand;

	this->cardsInHand = new list<Card>(hand.cardsInHand->begin(), hand.cardsInHand->end());

	return *this;
}

// Overloaded stream insertion operator
std::ostream& operator<<(std::ostream& output, const Hand& hand) {
	output << hand.getCards();

	return output;
}

// Overloaded stream extraction operator
istream& operator>>(istream& input, const Hand& hand){
	Card incard;
	input >> incard;
	hand.cardsInHand->push_back(incard);
	return input;
}
