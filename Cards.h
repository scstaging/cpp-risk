#pragma once
#include <iostream>
#include <list>
using namespace std;

class Card;
class Hand;
class Deck;

enum CardType { bomb, reinforcement, blockade, airlift, diplomacy };

class Card
{
	public:

		CardType* type;

		/**
		/	Default Constructor for Card Class
		*/
		Card();

		/**
		/	Specialized Constructor for Card Class
		*/
		Card(CardType type);

		/**
		/	Copy Constructor for Card Class
		*/
		Card(Card& copycard);
		
		/**
		/	Destructor 
		*/
		~Card();

		/**
		/	Plays the card, creating a special order for the player and adding card back to the deck.
		*/
		void play(Deck* deck, Hand* hand);

		/**
		/	Returns the type of the card
		*/
		CardType getType();

		/**
		/	Sets the type of the card
		*/
		void setType(CardType* newType);

        /**
        /   Returns the card type as a string
        */
        string cardTypeToString(CardType type);

};

class Deck 
{
	public:

		list<Card>* deckCards;

		int* deckSize;

		/**
		/	Default constructor for Deck class
		**/
		Deck();

		/**
		/	Specialized constructor for Deck class
		**/
		Deck(int numCards);

		/**
		/	Destructor
		*/
		~Deck();

		/**
		/	Draws a card from the deck, places it in hand
		*/
		string draw(Hand* hand);
		
		/**
		/	Adds a card of specific type to the deck.
		*/
		void addCard(CardType type);

		/**
		/	Lists the number of cards currently in the deck
		*/
		int getDeck();

		
};

class Hand
{
	public:
		/**
		/	List containing cards
		*/
		list<Card>* cardsInHand;

		/**
		/	Default constructor for hand class
		*/
		Hand();

		/**
		/	Destructor
		*/
		~Hand();

		/**
		/	Copy constructor for hand class
		*/
		Hand(Hand& hand);

		/**
		/	Adds a new card of a specific type to the player's hand
		*/
		void addCard(CardType& type);

        /**
		/	Adds a new card to the player's hand
		*/
        void addCard(Card& card);

		/**
		/	Removes a card of a specific type from the player's hand
		*/
		void removeCard(CardType& type);

		/**
		/	Returns cards in the player's hand
		*/
		string getCards();

};
