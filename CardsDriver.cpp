#include <iostream>
#include "Cards.h"
#include "Cards.cpp"

int testCards(){
    // Create a new deck
    Deck* testDeck = new Deck();

    // Return the size of the deck. Should be 15. 
    testDeck->getDeck();
    cout << "\n";

    // Creates a new hand 
    Hand* testHand = new Hand();

    // Draw five cards from the deck and place them in the hand
    for(int i = 0; i < 5; i++){
        testDeck->draw(testHand);
        cout << "\n";
    }

    // Return the size of the deck. Should be 10. 
    testDeck->getDeck();
    cout << "\n";

    // Create a list of cards and assign it to the cards in the hand
    list<Card> cards = *testHand->cardsInHand;

    // Play each card in the hand, depositing them back into the deck
    for(Card c : cards){
        c.play(testDeck, testHand);
    }

    // Return the size of the deck. Should be 15. 
    testDeck->getDeck();

    return 0;

}