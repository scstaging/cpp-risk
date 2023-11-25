#pragma once

#include <iostream>
#include "Player.h"
#include "PlayerStrategies.h"
#include "Orders.h"

// HumanPlayerStrategy Class

bool HumanPlayerStrategy::issueOrder(Player* player, Deck* deck, Map* map, GameEngine *game){
    if(*player->getReinforcementPool() > 0){
        cout << *player->getPlayerName() << ", it is your turn to issue an order. You still have reinforcements that must be deployed." << endl;
        cout << "Which territory would you like to deploy them in?" << endl;
        int counter = 0;

        for(Territory* t : toDefend(player)){
            cout << counter << ": " << t->getNameOfTerritory() << endl;
            counter++;
        }

        int userTerritoryChoice;
        cout << "Enter the number of the territory you would like to choose: ";
        cin >> userTerritoryChoice;

        Territory* territory = nullptr;

        vector<Territory*> defendedTerritories = player->getDefend();

        if(userTerritoryChoice >= 0 && userTerritoryChoice < toDefend(player).size()){    
            territory = defendedTerritories[userTerritoryChoice];
        }
        else{
            cout << "Invalid choice. Please try again." << endl;
        }

        string deployedTerritoryName = territory->getNameOfTerritory();

        int userTroopChoice;
        cout << "How many troops would you like to deploy? You have " << *player->getReinforcementPool() << " remaining in your reinforcement pool." << endl; 
        
        while(userTroopChoice > 0 && userTroopChoice <= *player->getReinforcementPool()){
            cin >> userTroopChoice;
        }
	    
        Deploy *deploy = new Deploy(player, deployedTerritoryName, userTroopChoice); // Updated to match the new Deploy constructor
	    

        player->getOrdersList()->addOrder(deploy);

        cout << "Troops deployed." << endl;

        *player->getReinforcementPool() -= userTroopChoice;
    }
    else{
        cout << *player->getPlayerName() << ", it is your turn to issue an order. What would you like to do?" << endl;
        int userChoice;

        list<int> options = list<int>(); 
        
        cout << "1. Advance" << endl;
        options.push_back(1);

        if(player->getHand()->getCardsInHand()->size() > 0){
            cout << "2. Play a card" << endl;
            options.push_back(2);
        }

        cout << "3. End your turn" << endl;
        options.push_back(3);

        while (std::find_if(options.begin(), options.end(),
            [userChoice](const auto& option) { return option == userChoice; }) != options.end()) {
            cin >> userChoice;
        }

        switch(userChoice){
            // Advance
            case 1:{
                cout << "Select your troops from which territory?" << endl;
                int counter = 0; 
                
                for(Territory* t : toDefend(player)){
                    cout << counter << ": " << t->getNameOfTerritory() << endl;
                    counter++;
                }

                int sourceTerritoryNumber;
                cout << "Enter the number of the territory you would like to choose: ";
                cin >> sourceTerritoryNumber;

                Territory* sourceTerritory = nullptr;

                vector<Territory*> defendedTerritories = player->getDefend();

                if(sourceTerritoryNumber >= 0 && sourceTerritoryNumber < toDefend(player).size()){    
                    sourceTerritory = defendedTerritories[sourceTerritoryNumber];
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
                for(Territory* t : this->toAttack(player)){
                    combinedAttackDefend.push_back(t);
                    cout << counter2 << ": " << t->getNameOfTerritory() << endl;
                    counter2++;
                }

                cout << "\n";

                cout << "Territories you can defend: " << endl;
                for(Territory* t : this->toDefend(player)){
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

		        Advance *advanceOrder = new Advance(player, sourceTerritory->getNameOfTerritory(), targetTerritory->getNameOfTerritory(), game, troopNumber);

                player->getOrdersList()->addOrder(advanceOrder);

                cout << "Advance order made." << endl;
                break;
            }
            // Card
            case 2:{

                cout << "Which card would you like to play?" << endl;
                int counter = 0; 

                auto& cardReference = *player->getHand()->getCardsInHand();


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

                userCard->play(deck, player->getHand());

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

vector<Territory*> HumanPlayerStrategy::toAttack(Player* player){

    vector<Territory*> territoriesToAttack = player->getAttack();

    for (unsigned int i = 0; i < territoriesToAttack.size(); i++) {
        cout << territoriesToAttack[i]->getNameOfTerritory() << "\n";
    }

    return territoriesToAttack;
}

vector<Territory*> HumanPlayerStrategy::toDefend(Player* player){

    vector<Territory*> territoriestoDefend = player->getDefend();

    for (unsigned int i = 0; i < territoriestoDefend.size(); i++) {
        cout << territoriestoDefend[i]->getNameOfTerritory() << "\n";
    }

    return territoriestoDefend;
}




