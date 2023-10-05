#include <iostream>
#include "Cards.h"
#include "Cards.cpp"

int main(){
    // Create a new deck
    Deck* testDeck = new Deck();

    cout << testDeck->getDeck();
    cout << "\n";

    // Creates a new hand 
    Hand* testHand = new Hand();

    // Draw five cards from the deck and place them in the hand
    for(int i = 0; i < 5; i++){
        testDeck->draw(testHand);
    }

    cout << testDeck->getDeck();
    cout << "\n";

    list<Card> cards = *testHand->cardsInHand;

    for(Card c : cards){
        c.play(testDeck, testHand);
    }

    cout << testDeck->getDeck();
    
    return 0;

}