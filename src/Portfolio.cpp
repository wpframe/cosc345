/*!
    @file
    @brief The implementation for the Portfolio class.
    @details It has the necessary data to store a collection of purchases.
*/

#include "Portfolio.h"
#include <iostream>
#include "Calendar.h"
#include <vector>
#include <algorithm>

/*!
    @brief Adds a purchase to the portfolio.
    @details If the stock is already in the portfolio, it updates the quantity and purchase price.
    @param purchase The purchase to add.
*/
void Portfolio::addPurchase(Purchase purchase, PositionType holdType)
{
    Purchase *existingPurchase = getPurchase(purchase.getStockSymbol(), holdType);
    float totalCost = purchase.calculateTotalCost();

    if (existingPurchase)
    {
        int newQuant = existingPurchase->getQuantity() + purchase.getQuantity();
        float firstPurchasePrice = existingPurchase->getQuantity() * existingPurchase->getPurchasePrice();
        
        float firstPrice = existingPurchase->getPurchasePrice();
        float updatedPurchasePrice = purchase.getQuantity() * purchase.getPurchasePrice();
        existingPurchase->setQuantity(newQuant);
        float byHandTotal = firstPurchasePrice + updatedPurchasePrice;
        existingPurchase->setPurchasePrice(byHandTotal / newQuant);

        if (holdType == PositionType::Short)
        {
            totalBalance += purchase.calculateTotalCost();
        }
        else
        {
            totalBalance -= purchase.calculateTotalCost();
        }
    }
    else
    {
        if (holdType == PositionType::Short)
        {
            totalBalance += purchase.calculateTotalCost();
            purchases.push_back(purchase);
        }
        else
        {
            totalBalance -= purchase.calculateTotalCost();
            purchases.push_back(purchase);
        }
    }
}

/*!
    @brief Adds a purchase to the portfolio.
    @details If the stock is already in the portfolio, it updates the quantity and purchase price.
    @param portfolio The portfolio to add the purchase to.
    @param selectedStock The stock to add to the portfolio.
    @param quantity The quantity of the stock to add.
    @param purchasePrice The purchase price of the stock.
    @param calendar The calendar to use for the purchase timestamp.
*/
void Portfolio::addPurchaseToPortfolio(Portfolio &portfolio, const Stock &selectedStock, int quantity, float purchasePrice, const Calendar &calendar, const std::string &purchaseType)
{
    PositionType type;
    if (purchaseType == "Short")
    {
        type = PositionType::Short;
    }
    else
    {
        type = PositionType::Long;
    }
    Purchase purchase(selectedStock, quantity, purchasePrice, calendar.getDate(), type);
    portfolio.addPurchase(purchase, type);
}

/*!
    @brief Sells a purchase from the portfolio and adds the value back to the total balance.
    @param stockSymbol The stock symbol to sell.
    @param quantityToSell The quantity of the stock to sell.
    @param currentPrice The current price of the stock.
    @return True if the sale was successful, false otherwise.
*/
void Portfolio::sellPurchase(const Stock &selectedStock, int quantityToSell, float currentPrice, PositionType holdType)
{
    // Find the purchase with the selected stock and holdType
    auto purchaseToSell = std::find_if(purchases.begin(), purchases.end(), [&](const Purchase &purchase)
                                       { return purchase.getStockSymbol() == selectedStock.getSymbol() && purchase.getPositionType() == holdType; });

    if (purchaseToSell == purchases.end())
    {
        std::string holdTypeStr;
        if (holdType == PositionType::Short)
        {
            holdTypeStr = "short";
        }
        else
        {
            holdTypeStr = "long";
        }

        std::cout << "No purchase found for " << selectedStock.getSymbol() << " with PositionType " << holdTypeStr << std::endl;
        return;
    }

    if (holdType == PositionType::Long)
    {
        // If the position is Long, sell as usual
        if (purchaseToSell->getQuantity() >= quantityToSell)
        {
            int remainingQuantity = purchaseToSell->getQuantity() - quantityToSell;
            float saleValue = quantityToSell * currentPrice;
            totalBalance += saleValue;

            if (remainingQuantity > 0)
            {
                purchaseToSell->setQuantity(remainingQuantity);
            }
            else
            {
                // Remove the purchase if the quantity becomes zero
                purchases.erase(purchaseToSell);
            }

            std::cout << "Sold " << quantityToSell << " shares of " << selectedStock.getSymbol() << " at $" << currentPrice << " each." << std::endl;
        }
        else
        {
            std::cout << "Insufficient quantity to sell." << std::endl;
        }
    }
    else if (holdType == PositionType::Short)
    {
        // If the position is Short, buy back shorts (cover the short position)
        int shortQuantity = purchaseToSell->getQuantity(); // Quantity of shorts to buy back
        float purchaseValue = shortQuantity * currentPrice;
        totalBalance -= purchaseValue; // Deduct the cost of buying back shorts

        // Remove the short position from the portfolio
        purchases.erase(purchaseToSell);

        std::cout << "Bought back " << shortQuantity << " shares of " << selectedStock.getSymbol() << " (Short Cover) at $" << currentPrice << " each." << std::endl;
    }
    else
    {
        std::cout << "Invalid PositionType." << std::endl;
    }
}

/*!
    @brief Getter for total balance of player.
    @return A float, the total balance.
*/
float Portfolio::getTotalBalance() const
{
    return totalBalance;
}

/*!
    @brief Prints the portfolio to stdout.
*/
void Portfolio::printPortfolio() const
{
    std::cout << "Portfolio Details:" << std::endl;
    for (const Purchase &purchase : purchases)
    {
        std::cout << "------------------------------" << std::endl;
        purchase.printPurchaseDetails();
    }
}

/*!
    @brief Gets a purchase for a specific stock from the portfolio.
    @param stockSymbol The stock symbol of the purchase to get.
    @return A pointer to the purchase if it exists, nullptr otherwise.
*/
Purchase *Portfolio::getPurchase(const std::string &stockSymbol, PositionType holdType)
{
    for (Purchase &purchase : purchases)
    {
        if (purchase.getStockSymbol() == stockSymbol && holdType == purchase.getPositionType())
        {
            return &purchase;
        }
    }
    return nullptr;
}

/*!
    @brief Accessor for the Purchase vector in the portfolio.
    @return A vector of all the purchases in the portfolio.
*/
const std::vector<Purchase> Portfolio::getPurchases() const
{
    return purchases;
}

/*!
    @brief Prints a summary of the portfolio to stdout. This is only used in testing.
    @param time The time to use for the summary.
*/
void Portfolio::summarizePortfolio(int time) const
{
    float totalInvestment = 0.0;
    float currentValue = 0.0;

    std::cout << "**************************" << std::endl;
    std::cout << "Portfolio Summary:" << std::endl;
    for (const Purchase &purchase : purchases)
    {
        float purchaseValue = purchase.getQuantity() * purchase.getPurchasePrice();
        totalInvestment += purchaseValue;

        float currentPrice = purchase.getStock().history[time].closePrice;

        float currentPurchaseValue = purchase.getQuantity() * currentPrice;
        currentValue += currentPurchaseValue;

        std::cout << "Stock Symbol: " << purchase.getStockSymbol() << std::endl;
        std::cout << "Average Purchase Price: " << purchase.getPurchasePrice() << std::endl;
        std::cout << "Current Price: " << currentPrice << std::endl;
        std::cout << "Quantity: " << purchase.getQuantity() << std::endl;
        std::cout << "Purchase Value: " << purchaseValue << std::endl;
        std::cout << "Current Value: " << currentPurchaseValue << std::endl;

        // Calculate and display profit/loss percentage
        float profitLoss = currentPurchaseValue - purchaseValue;
        float profitLossPercentage = (profitLoss / purchaseValue) * 100.0;
        std::cout << "Profit/Loss: " << profitLossPercentage << "%" << std::endl;

        std::cout << "--------------------------" << std::endl;
    }

    float totalProfitLoss = currentValue - totalInvestment;
    float totalProfitLossPercentage = (totalProfitLoss / totalInvestment) * 100.0;

    std::cout << "Total Investment: " << totalInvestment << std::endl;
    std::cout << "Current Portfolio Value: " << currentValue << std::endl;
    std::cout << "Total Profit/Loss: " << totalProfitLoss << std::endl;
    std::cout << "Total Profit/Loss Percentage: " << totalProfitLossPercentage << "%" << std::endl;
}
