#pragma once

#include <iostream>
#include <random>
#include "Player.h"
#include "PlayerStrategies.h"
#include "Orders.h"
#include <algorithm>

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

    for(Territory* t : player->getTerritories()){
        for(Territory* adjacent : t->getAdjacentTerritory()){
            if(adjacent->getOwnerPlayerName() != player->getPlayerName()){
                territoriesToAttack.push_back(adjacent);
            }
        }
    }

    return territoriesToAttack;
}

vector<Territory*> HumanPlayerStrategy::toDefend(Player* player){

    return player->getTerritories();
}

// AggressivePlayerStrategy Class

Territory* AggressivePlayerStrategy::getStrongestTerritory(){
    return strongestTerritory;
}

void AggressivePlayerStrategy::setStrongestTerritory(Player* player){
    this->strongestTerritory = player->getTerritories()[0];
    for(int i = 0; i < player->getTerritories().size(); i++){
        if(player->getTerritories()[i]->getNumArmies() > strongestTerritory->getNumArmies()){
            this->strongestTerritory = player->getTerritories()[i];
        }
    }
}

bool AggressivePlayerStrategy::issueOrder(Player* player, Deck* deck, Map* map, GameEngine *game){

    std::random_device rd;
    std::mt19937 mt(rd());
    bool advance;

    //updates the current player's strongest territory.
    setStrongestTerritory(player);

    //Will automatically deploy a random number of troops into the strongest territory
    if(*player->getReinforcementPool() > 0){
        
        //Produces a random number between 1 and the size of the player's reinforcement pool
        std::uniform_int_distribution<int> distribution(1, *player->getReinforcementPool());
        int aggTroopChoice = distribution(mt);
	    
        //Deploys the random number of troops
        Deploy *deploy = new Deploy(player, strongestTerritory->getNameOfTerritory(), aggTroopChoice); 

        player->getOrdersList()->addOrder(deploy);

        cout << "AggressivePlayer Troops deployed." << endl;
        
        advance = true;

        //Subtracts random number of troops from reinforcement
        *player->getReinforcementPool() -= aggTroopChoice;
    }
    else{
        int aggChoice;

        list<int> options = list<int>(); 
        
        //Option to advance
        if(advance){
            options.push_back(1);
        }

        //Option to play a card
        if(player->getHand()->getCardsInHand()->size() > 0){
            options.push_back(2);
        }

        //Option to end turn
        options.push_back(3);

        std::uniform_int_distribution<int> distribution(1, options.size() - 1);

        //Chooses random number corresponding to action from the options list
        aggChoice = distribution(mt);

        switch(aggChoice){
            // Advance
            case 1:{

                int sourceTerritoryNumber;

                Territory* sourceTerritory = nullptr;

                //Gets list of territories within the player's control
                vector<Territory*> defendedTerritories = player->getDefend();

                for(int i = 0; i < defendedTerritories.size(); i++){

                    int* numTroops = defendedTerritories[i]->getNumArmies();

                    if(numTroops > 0){
                        //List of territories the player can attack. 
                        vector<Territory*> attackOptions;
                        int counter;

                        //cycles through all of the territories adjacent to the current territory
                        for(int j = 0; i < toDefend(player)[i]->getAdjacentTerritory().size(); j++){
                            //Checks to see if a territory is either owned by no one or owned by another player. Adds that territory to a list of attackable territories if this is the case.
                            if(toDefend(player)[i]->getAdjacentTerritory()[j]->getOwnerPlayerName() == nullptr || player->getPlayerName() != toDefend(player)[i]->getAdjacentTerritory()[j]->getOwnerPlayerName()){
                                attackOptions[counter] = toDefend(player)[i]->getAdjacentTerritory()[j];
                                counter++;
                            }
                        }
                        if(attackOptions.size() == 0){
                            //If no adjacent territories can be attacked, and the current territory is the strongest territory, sent troops to random adjacent territory.
                            if(defendedTerritories[i]->getNameOfTerritory() == strongestTerritory->getNameOfTerritory()){
                                std::uniform_int_distribution<int> distribution(0, strongestTerritory->getAdjacentTerritory().size() - 1);
                                int destinationChoice = distribution(mt);

                                Advance *advanceOrder = new Advance(player, defendedTerritories[i]->getNameOfTerritory(), strongestTerritory->getAdjacentTerritory()[destinationChoice]->getNameOfTerritory(), game, *numTroops);
                            
                                player->getOrdersList()->addOrder(advanceOrder);
                            }
                            //If the current territory is not the strongest territory, advances troops to the strongest territory.
                            else{
                                Advance *advanceOrder = new Advance(player, defendedTerritories[i]->getNameOfTerritory(), strongestTerritory->getNameOfTerritory(), game, *numTroops);
                            }
                        }
                        //Sends troops to random attackable adjacent territory.
                        else{
                            std::uniform_int_distribution<int> distribution(0, attackOptions.size() - 1);
                            int destinationChoice = distribution(mt);        

                            Territory* attackChoice = attackOptions[destinationChoice];                

                            Advance *advanceOrder = new Advance(player, defendedTerritories[i]->getNameOfTerritory(), attackChoice->getNameOfTerritory(), game, *numTroops);    
                        }
                    }
                }
                advance = false;
                break;

            }
            // Card (can only play bomb card)
            case 2:{
                auto& cardReference = *player->getHand()->getCardsInHand();

		        vector<Card *> cards;

            	for (Card &card : cardReference)
            	{
                	cards.push_back(&card);
            	}

                Card* userCard = nullptr;

                int count = 0;
                
                //Cycles through player's list of cards until it sees a bomb card, in which case it executes the bomb card. If not bomb card found, ends.
                for(int i = 0; i < cards.size(); i++){
                    if(cards[i]->getType() == bomb){
                        userCard = cards[i];
                        userCard->play(deck, player->getHand());
                        count++;
                        break;
                    }
                }

                if(count == 0){
                    cout << "No cards to play" << endl;
                }

                break;
            }
            case 3:{
                //Ends turn
                return false;
            }
            default:{
		        throw std::runtime_error("Invalid choice. Please try again.");
            }
        }
    }
    return true;

}

vector<Territory*> AggressivePlayerStrategy::toAttack(Player* player){

    vector<Territory*> territoriesToAttack = player->getAttack();

    for(Territory* t : player->getTerritories()){
        for(Territory* adjacent : t->getAdjacentTerritory()){
            if(adjacent->getOwnerPlayerName() != player->getPlayerName()){
                territoriesToAttack.push_back(adjacent);
            }
        }
    }

    return territoriesToAttack;
}

vector<Territory*> AggressivePlayerStrategy::toDefend(Player* player){

    return player->getTerritories();
}

// ** BENEVOLENT PLAYER ** //
Territory* BenevolentPlayerStrategy::getWeakestTerritory(){
    return weakestTerritory;
}

void BenevolentPlayerStrategy::setWeakestTerritory(Player* player){
    // Bubble Sort?
    // Sets weakest territory as first Benevolent player element
    this->weakestTerritory = player->toDefend()[0];

    // Iterates through Benevolent player territories
    for(int i = 0; i < player->toDefend().size(); i++)
    {
        // Sets weakest territory through bubble sort-like method
        if(player->toDefend()[i]->getNumArmies() < weakestTerritory->getNumArmies())
        {
            this->weakestTerritory = player->toDefend()[i];
        }
    }
}

bool BenevolentPlayerStrategy::issueOrder(Player* player, Deck* deck, Map* map, GameEngine *game)
{
    cout << "Benevolent Player's turn" << endl;
    cout << "Benevolent Player draws a card" << endl;

    deck->draw(player->getHand());

    std::random_device rd;
    std::mt19937 mt(rd());

    //updates the current player's strongest territory.
    setWeakestTerritory(player);

    //Will automatically deploy a random number of troops into the weakest territory
    if(*player->getReinforcementPool() > 0){
        
        //Produces a random number between 1 and the size of the player's reinforcement pool
        std::uniform_int_distribution<int> distribution(1, *player->getReinforcementPool());
        int benTroopChoice = distribution(mt);
	    
        //Deploys the random number of troops
        Deploy *deploy = new Deploy(player, weakestTerritory->getNameOfTerritory(), benTroopChoice); 

        player->getOrdersList()->addOrder(deploy);

        cout << "Benevolent Player Troops deployed." << endl;
        cout << "Benevolent Player reinforced " + weakestTerritory->getNameOfTerritory() << endl;

        //Subtracts random number of troops from reinforcement
        *player->getReinforcementPool() -= benTroopChoice;
    }

    // Doesn't have reinforcements to deploy
    else
    {
        int benevolentChoice;

        list<int> options = list<int>(); 
        
        //Option to play a card
        if(player->getHand()->getCardsInHand()->size() > 0){
            options.push_back(1);
        }

        //Option to end turn
        options.push_back(2);

        // Random number between 1 and 2 for choice
        std::uniform_int_distribution<int> distribution(1, options.size() - 1);

        //Chooses random number corresponding to action from the options list
        benevolentChoice = distribution(mt);

        switch (benevolentChoice)
        {
        case 1:
        {
            auto& cardReference = *player->getHand()->getCardsInHand();

		    vector<Card *> cards;

            for (Card &card : cardReference)
            {
                cards.push_back(&card);
            }

            Card* userCard = nullptr;

            int count = 0;
                
            // Cycles through player's cards until it sees a card that is not a bomb or an airlift. If so, plays the card
            for(int i = 0; i < cards.size(); i++)
            {
                if(cards[i]->getType() != bomb && cards[i]->getType() != airlift)
                {
                    userCard = cards[i];
                    userCard->play(deck, player->getHand());
                    count++;
                    break;
                }
            }

            if(count == 0){
                cout << "No cards the Benevolent wants to play" << std::endl;
            }
            break;
        }
        case 2:
        {
            //Ends turn
            cout << "Benevolent decides to end his turn." << std::endl;
            return false;
        }
        }
    }

}

// List of attackable territories for Benevolent Player
    // (This is created for the sake of redundency)
vector<Territory*> BenevolentPlayerStrategy::toAttack(Player* player)
{
    // Creates empty vector array
    vector<Territory*> attackable = {};

    // Returns empty vector array
    return attackable;
}

// List of territories under Benevolent Player control
vector<Territory*> BenevolentPlayerStrategy::toDefend(Player* player)
{
    return player->getTerritories();
}
// ** END BENEVOLENT PLAYER ** //

// ** NEUTRAL PLAYER ** //
bool NeutralPlayerStrategy::issueOrder(Player* player, Deck* deck, Map* map, GameEngine *game)
{
    cout << "Neutral Player turn" << endl;
    cout << "Neutral Player draws a card" << endl;

    // Draws card
    deck->draw(player->getHand());

    // Ends turn
    cout << "Neutral Player ends his turn" << endl;
    
    return false;
}
// ** END NEUTRAL PLAYER ** //

// ** CHEATER PLAYER ** //
bool CheaterPlayerStrategy::issueOrder(Player* player, Deck* deck, Map* map, GameEngine *game)
{
    cout << "Cheater Player turn" << endl;
    cout << "Cheater player draws a card" << endl;

    deck->draw(player->getHand());

    std::random_device rd;
    std::mt19937 mt(rd());

    //Will automatically deploy a random number of troops into the weakest territory
    if(*player->getReinforcementPool() > 0)
    {
        Territory* toReinforce;

        // Gets random index from 0 to number of player territories - 1
        int randIndex = std::rand() % player->toDefend().size();

        // Sets territory to reinforce to a random territory under control of cheater
        toReinforce = player->getTerritories()[randIndex];

        //Produces a random number between 1 and the size of the player's reinforcement pool
        std::uniform_int_distribution<int> distribution(1, *player->getReinforcementPool());

        // Computer 'decides' to reinforce random territory with arbitrary amount of troops
        int cheaterTroopChoice = distribution(mt);
	    
        //Deploys the random number of troops to random territory
        Deploy *deploy = new Deploy(player, toReinforce->getNameOfTerritory(), cheaterTroopChoice); 

        player->getOrdersList()->addOrder(deploy);

        cout << "Cheater Player Troops deployed." << endl;
        cout << "Cheater Player reinforced " + toReinforce->getNameOfTerritory() << endl;

        //Subtracts random number of troops from reinforcement
        *player->getReinforcementPool() -= cheaterTroopChoice;
    }

    // Get list of adjacent territories to computer player
    vector<Territory*> toConquer = player->toAttack();

    // Immeditetly 'conquer' territories
        // (Set all adjacent territories to cheater player control and remove from other players without condition)
    for (int i = 0; i < toConquer.size(); i++)
    {
        // Display conquering message
        cout << "Cheater has conquered " + toConquer[i]->getNameOfTerritory() << endl;

        // Draw card for conquered territory
        deck->draw(player->getHand());

        // Transfers ownership
        toConquer[i]->setOwnerPlayer(player);
    }
}

// List of adjacent territories to Cheataer Player
vector<Territory*> CheaterPlayerStrategy::toAttack(Player* player){

    vector<Territory*> territoriesToAttack = player->getAttack();

    for(Territory* t : player->getTerritories()){
        for(Territory* adjacent : t->getAdjacentTerritory()){
            if(adjacent->getOwnerPlayerName() != player->getPlayerName()){
                territoriesToAttack.push_back(adjacent);
            }
        }
    }

    return territoriesToAttack;
}

// List of territories under Cheater Player control
vector<Territory*> CheaterPlayerStrategy::toDefend(Player* player){

    return player->getTerritories();
}
// ** END CHEATER PLAYER ** //