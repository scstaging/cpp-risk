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
		Card(const Card &copycard);
		
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
		CardType getType() const;

		/**
		/	Sets the type of the card
		*/
		void setType(CardType* newType);

        /**
        /   Returns the card type as a string
        */
        string cardTypeToString(CardType type) const;
		
		// Assignment operator
		Card& operator=(const Card& card);

		// Stream insertion operator
		friend std::ostream&operator<<(std::ostream& output, const Card& card);

		// Stream extraction operator
		friend std::istream& operator>>(std::istream& input, Card& card);

	private:
		CardType* type;
};

class Deck 
{
	public:

		/**
		/	Default constructor for Deck class
		**/
		Deck();

		/**
		/	Specialized constructor for Deck class
		**/
		Deck(int numCards);

		/**
		 * Copy constructor for Deck class
		 */
		Deck(Deck &copydeck);

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
		int getDeckSize() const;

		// Assignment operator
		Deck& operator=(const Deck& deck);

		// Stream insertion operator
		friend std::ostream&operator<<(std::ostream& output, const Deck& deck);

		// Stream extraction operator
		friend std::istream& operator>>(std::istream& input, const Deck& deck);

		private:
			list<Card>* deckCards;

			int* deckSize;
};

class Hand
{
	public:

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
		string getCards() const;

		list<Card>* getCardsInHand() const;

		// Assignment operator
		Hand& operator=(const Hand& hand);

		// Stream insertion operator
		friend std::ostream&operator<<(std::ostream& output, const Hand& hand);

		// Stream extraction operator
		friend std::istream& operator>>(std::istream& input, const Hand& hand);

	private:
		/**
		/	List containing cards
		*/
		list<Card>* cardsInHand;
};

int testCards();
