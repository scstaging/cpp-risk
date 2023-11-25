#pragma once

#include "Map.h"
#include "Player.h"

/**
 * @brief Strategy class that other concrete strategy classes will inherit
 * 
 */
class PlayerStrategy {

    PlayerStrategy();
    virtual ~PlayerStrategy();

    virtual bool issueOrder(Deck* deck, Map* map, GameEngine *game);
    virtual vector<Territory*> toDefend(Player *player) = 0;
    virtual vector<Territory*> toAttack(Player *player) = 0;
};

/**
 * @brief Concreate stategy class for human user
 * 
 */
class HumanPlayerStrategy : public PlayerStrategy{
    virtual bool issueOrder(Deck* deck, Map* map, GameEngine *game);
    virtual vector<Territory*> toDefend(Player *player) = 0;
    virtual vector<Territory*> toAttack(Player *player) = 0;

};

/**
 * @brief Concrete strategy class for aggressive player. Will focus on attacking and only deploy/advance armies onto its strongest country.
 * 
 */
class AggressivePlayerStrategy: public PlayerStrategy{

    protected:
    Territory* strongestTerritory;

    public:

    Territory* getStrongestTerritory();
    void setStrongestTerritory(Player* player);
    virtual bool issueOrder(Deck* deck, Map* map, GameEngine *game);
    virtual vector<Territory*> toDefend(Player *player) = 0;
    virtual vector<Territory*> toAttack(Player *player) = 0;

};

/**
 * @brief Concrete stategy class for benevolent player. Will focus on defending and only deploy/advance armies onto its weakest country.
 * 
 */
class BenevolentPlayerStrategy: public PlayerStrategy{

    protected:
    Territory* weakestTerritory;

    public:

    Territory* getWeakestTerritory();
    void setWeakestTerritory(Player* player);
    virtual bool issueOrder(Deck* deck, Map* map, GameEngine *game);
    virtual vector<Territory*> toDefend(Player *player) = 0;
    virtual vector<Territory*> toAttack(Player *player) = 0;

};

/**
 * @brief Concrete strategy class for neutral player. Will not play unless it is attacked, at which point it becomes an aggressive user.
 * 
 */
class NeutralPlayerStrategy: public PlayerStrategy{
    
    protected:
    bool aggressive;

    public:

    virtual bool issueOrder(Deck* deck, Map* map, GameEngine *game);
    virtual vector<Territory*> toDefend(Player *player) = 0;
    virtual vector<Territory*> toAttack(Player *player) = 0;

};

/**
 * @brief Concrete strategy class for cheater player. Will automatically conquer all territories that are adjacent to its own. 
 * 
 */
class CheaterPlayerStrategy: public PlayerStrategy{
    virtual bool issueOrder(Deck* deck, Map* map, GameEngine *game);
    virtual vector<Territory*> toDefend(Player *player) = 0;
    virtual vector<Territory*> toAttack(Player *player) = 0;
};



