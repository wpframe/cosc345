#ifndef GAME_FUNCTIONS_H
#define GAME_FUNCTIONS_H

#include "Purchase.h"
#include <vector>

class GameFunctions
{
public:
    std::vector<Purchase> purchases;
    float totalBalance;
    static void endGame(int TIMECOUNT, std::vector<Stock> &stocks);
    static void resetGame(int TIMECOUNT, std::vector<Stock> &stocks);
};

#endif // GAME_FUNCTIONS_H
