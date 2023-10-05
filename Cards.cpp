#pragma once
#include <iostream>
using namespace std;

#include "Cards.h"

//Card class

Card::Card() {
    type = new CardType(bomb);
}

Card::Card(CardType spectype){
    type = new CardType(spectype);
}

Card::Card(Card& copycard) {
	type = new CardType(*copycard.type);
}

Card::~Card() {
	delete this->type;
	this->type = nullptr;
}

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
			cout << "This is a card of type blockade. \n";
			break;
		}
		case airlift:
		{
			cout << "This is a card of type airlift. \n";
			break;
		}
		case diplomacy:
		{
			cout << "This is a card of type diplomacy. \n";
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

CardType Card::getType() {
    return *this->type;
}

void Card::setType(CardType* newType){
    this->type = newType;
}

string Card::cardTypeToString(CardType type){
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

// Deck class

Deck::Deck() {
	list <Card>* cardList = new list<Card>();

	//Defaults the number cards to 3 each
	for (int i = 0; i < 3; i++) {
		cardList->push_back(*new Card(bomb));
		cardList->push_back(*new Card(reinforcement));
		cardList->push_back(*new Card(blockade));
		cardList->push_back(*new Card(airlift));
		cardList->push_back(*new Card(diplomacy));
	}	

	this->deckCards = cardList;
}

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
}

void Deck::addCard(CardType type) {
	Card* newCard = new Card(type);
	deckCards->push_back(*newCard);
}

int Deck::getDeck() {
	return deckCards->size();
}

// Hand class

Hand::Hand() {
	this->cardsInHand = new list<Card>();
}

Hand::~Hand() {
	delete this->cardsInHand;
	this->cardsInHand = nullptr;
}

void Hand::addCard(CardType& type) {
	Card* newCard = new Card(type);
	cardsInHand->push_back(*newCard);
}

void Hand::removeCard(CardType& type) {
	list<Card>::iterator it;

	for (it = cardsInHand->begin(); it != cardsInHand->end(); ++it) {
		if (*it->type == type) {
			cardsInHand->erase(it);
			return;
		}
	}
}

string Hand::getCards() {
	cout << "This hand has the following cards:";

	string *result = new string("");

	for (Card& card : *cardsInHand) {
		*result += card.cardTypeToString(card.getType()); + " ";
	}

	return *result;
}