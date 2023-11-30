#pragma once

#include "Map.h"
#include "Player.h"

/**
 * @brief Strategy class that other concrete strategy classes will inherit
 * 
 */
class PlayerStrategy {

    public:
        PlayerStrategy();
        virtual ~PlayerStrategy();

        virtual bool issueOrder(Player* player, Deck* deck, Map* map, GameEngine *game) = 0;
        virtual vector<Territory*> toDefend(Player *player) = 0;
        virtual vector<Territory*> toAttack(Player *player) = 0;
};

/**
 * @brief Concrete stategy class for human user
 * 
 */
class HumanPlayerStrategy : public PlayerStrategy{

    public: 
        bool issueOrder(Player* player, Deck* deck, Map* map, GameEngine *game);
        vector<Territory*> toDefend(Player *player) = 0;
        vector<Territory*> toAttack(Player *player) = 0;

};

/**
 * @brief Concrete strategy class for aggressive player. Will focus on attacking and only deploy/advance armies onto its strongest country.
 *        Can only play cards that have an aggressive purpose (presumably only bomb)
 * 
 */
class AggressivePlayerStrategy: public PlayerStrategy{

    protected:
        Territory* strongestTerritory;

    public:
        Territory* getStrongestTerritory();
        void setStrongestTerritory(Player* player);
        bool issueOrder(Player* player, Deck* deck, Map* map, GameEngine *game);
        vector<Territory*> toDefend(Player *player);
        vector<Territory*> toAttack(Player *player);

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
        bool issueOrder(Player* player, Deck* deck, Map* map, GameEngine *game);
        vector<Territory*> toDefend(Player *player);
        vector<Territory*> toAttack(Player *player);

};

/**
 * @brief Concrete strategy class for neutral player. Will not play unless it is attacked, at which point it becomes an aggressive user.
 * 
 */
class NeutralPlayerStrategy: public PlayerStrategy{
    
    protected:
        bool aggressive;

    public:
        bool issueOrder(Player* player, Deck* deck, Map* map, GameEngine *game);
        vector<Territory*> toDefend(Player *player);
        vector<Territory*> toAttack(Player *player);

};

/**
 * @brief Concrete strategy class for cheater player. Will automatically conquer all territories that are adjacent to its own. 
 * 
 */
class CheaterPlayerStrategy: public PlayerStrategy{

    public:
        bool issueOrder(Player* player, Deck* deck, Map* map, GameEngine *game);
        vector<Territory*> toDefend(Player *player);
        vector<Territory*> toAttack(Player *player);

};



