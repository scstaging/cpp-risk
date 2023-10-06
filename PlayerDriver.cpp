#include "Player.h"
#include "Cards.h"
#include "PlayerDriver.h"

#include <iostream>

using std::cout;
using std::endl;

void testPlayers()
{
    /* 
    This free function tests the Player class by creating player objects and demonstrating that the player objects have the following specified features:
        - Player owns a collection of territories
        - Player owns a hand of cards
        - Player contains following methods:
            - issueOrder(): creates an order object and adds it to the player's list of orders
            - toAttack(): returns arbitrary (for now) list of territories that are to be attacked
            - toDefend(): returns arbitrary (for now) list of territories that are to be defended
        - Copy constructor implemented
        - Overloaded assignment operator implemented
        - Overloaded stream insertion operator implemented
    */

    cout << "**** Testing player functionality ****\n";

    cout << "\n**** Testing Player Default Constructor ****\n";
    
    Player * p1 = new Player();

    cout << "Player p1 name: " << *p1->getPlayerName() << endl;
    
    cout << "\n**** Testing Player Constructor with name parameter ****\n";
    
    Player * p2 = new Player("Zack");

    cout << "Player p2 name: " << *p2->getPlayerName() << endl;

    cout << "\n**** Testing Player Copy Constructor ****\n";

    Player * copiedPlayer = new Player(*p2);

    cout << "Player copiedPlayer name: " << *copiedPlayer->getPlayerName() << endl;

    cout << "\n**** Testing player stream insertion operator overloading ****\n";

    cout << *p2;

    cout << "\n**** Testing player assignment operator overloading ****\n";

    *p1 = *p2;

    cout << "Address of pointer p2: " << p2 << endl;

    cout << "Values of player p2:\n" << *p2 << endl;

    cout << "Address of pointer p1: " << p1 << endl;

    cout << "Values of player p1 after assignment from p2:\n" << *p1 << endl;

    cout << "Player p1's empty hand: " << *p1->getHand();

    Deck* testDeck = new Deck();
    cout << "Test deck created. Drawing 5 cards from deck into player's hand:\n\n";

    for(int i = 0; i < 5; i++){
        testDeck->draw(p1->getHand());
    }

    cout << "Player p1's hand: " << *p1->getHand() << endl;

    /* TEST: issueOrder() */

    /* TEST: toAttack() */

    /* TEST: toDefend() */

    delete p1;

    delete p2;

    delete copiedPlayer;

    delete testDeck;

    return;
}
