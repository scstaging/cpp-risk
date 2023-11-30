#include "PlayerStrategies.h"
#include "GameEngine.h"
#include "Map.h"
#include "Orders.h"
#include "Cards.h"
#include "Player.h"
#include <algorithm>

void testPlayerStrategies()
{
    std::vector<PlayerStrategy*> strats = {new AggressivePlayerStrategy(), new BenevolentPlayerStrategy(), new NeutralPlayerStrategy(), new CheaterPlayerStrategy()};

    // Instantiates 4 computer players
    Player* aggressive = new Player("aggressive", strats[0]);
    Player* benevolent = new Player("benevolent", strats[1]);
    Player* neutral = new Player("neutral", strats[2]);
    Player* cheater = new Player("cheater", strats[3]);

    // Memory safe
    delete(aggressive);
    aggressive = nullptr;
    delete(benevolent);
    benevolent = nullptr;
    delete(neutral);
    neutral = nullptr;
    delete(cheater);
    cheater = nullptr;
}