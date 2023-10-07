#include <iostream>
#include "Cards.h"
#include "CardsDriver.h"

using std::cout;

int testCards(){
    cout << "\n**** Testing player functionality ****\n";

    // Create a new deck
    Deck* testDeck = new Deck();
    cout << "Deck created. \n\n";

    cout << "Current size of the deck: ";
    cout << testDeck->getDeckSize();
    cout << "\n\n";

    // Creates a new hand 
    Hand* testHand = new Hand();

    // Draw five cards from the deck and place them in the hand
    for(int i = 0; i < 5; i++){
        testDeck->draw(testHand);
    }

    cout << *testHand << "\n";

    // Return the size of the deck. Should be 10. 
    cout << "Current size of the deck: ";
    cout << testDeck->getDeckSize() << "\n\n";
  

    // Create a list of cards and assign it to the cards in the had
    list<Card> cards = *testHand->getCardsInHand();

    // Play each card in the hand, depositing them back into the deck
    for(Card c : cards){
        c.play(testDeck, testHand);
    }
    cout << "\n";

    // Return size of the deck. Should be 15.
    cout << "Current size of the deck: ";
    cout << testDeck->getDeckSize();
    
    return 0;

}
