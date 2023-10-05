#include <iostream>
#include "Cards.h"
#include "Cards.cpp"

int testCards(){

    Deck* testDeck = new Deck();

    testDeck->getDeck();

    Hand* testHand = new Hand();

    for(int i = 0; i < 5; i++){
        testDeck->draw(testHand);
    }

    list<Card> cards = *testHand->cardsInHand;

    for(Card c : cards){
        c.play(testDeck, testHand);
    }


}