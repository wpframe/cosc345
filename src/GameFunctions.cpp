#include "Purchase.h"
#include "Portfolio.h"
#include "Stock.h"
#include "GameFunctions.h"
#include "Portfolio.h"
#include <vector>
#include <iostream>

/*!
    @file
    @brief Class which can end and reset the game state.
    @author Ben Knox
*/

/*!
    @brief Method which will sell all stocks in the portfolio
    @param TIMECOUNT [in] current week number
    @param stocks [in] the vector of stocks
*/
void GameFunctions::endGame(int TIMECOUNT, std::vector<Stock> &stocks)
{

    std::vector<Purchase> purchases = portfolio.getPurchases();
    for (const Purchase &purchase : purchases)
    {
        Stock selectedStock = purchase.getStock();
        float currentPriceFloat = selectedStock.history[TIMECOUNT].closePrice;
        portfolio.sellPurchase(selectedStock, purchase.getQuantity(), currentPriceFloat, purchase.getPositionType());
    }

    // Add to leaderboard
}

/*!
    @brief Method clears the history of all stocks.
    @param TIMECOUNT [in] current week number
    @param stocks [in] the vector of stocks
*/
void GameFunctions::resetGame(int TIMECOUNT, std::vector<Stock> &stocks)
{
    portfolio.resetTotalBalance();

    for (auto &stock : stocks)
    {
        stock.history.clear();
    }

    // TIMECOUNT = 0;
    // latestDate = gameStartDate;
    // careerStage = 0;
    // tuitionNeedsPaid = 0;
    // salaryNeedsPaid = 0;
    // lastTuitionPaidYear = 0;
    // lastPromotion = "";
}
