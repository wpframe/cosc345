/*!
    @file
    @brief The implementation for the Portfolio class.
    @details It has the necessary data to store a collection of purchases.
*/

#include "Portfolio.h"
#include <iostream>
#include "Calendar.h"

/*!
    @brief Adds a purchase to the portfolio.
    @details If the stock is already in the portfolio, it updates the quantity and purchase price.
    @param purchase The purchase to add.
*/
void Portfolio::addPurchase(Purchase purchase)
{
    int count = 1;
    Purchase *existingPurchase = getPurchase(purchase.getStockSymbol());

    if (existingPurchase)
    {
        count++;
        int newQuant = existingPurchase->getQuantity() + purchase.getQuantity();
        float firstPurchasePrice = existingPurchase->getQuantity() * existingPurchase->getPurchasePrice();
        int firstQuant = existingPurchase->getQuantity();
        float firstPrice = existingPurchase->getPurchasePrice();
        float updatedPurchasePrice = purchase.getQuantity() * purchase.getPurchasePrice();

        std::cout << "UdatedQuant: " << newQuant << std::endl;
        existingPurchase->setQuantity(newQuant);

        std::cout << "first: " << firstPurchasePrice << std::endl;

        std::cout << "second: " << updatedPurchasePrice << std::endl;

        // IS NOT SETING TOTAL COST CORRECTLY AT THE MOMENT, NEED TO IMPLEMENT SETTOTAL() WILL BE EEASY
        float totalCost = existingPurchase->calculateTotalCost() + purchase.calculateTotalCost();

        float byHandTotal = firstPurchasePrice + updatedPurchasePrice;
        std::cout << "tptalCost: " << byHandTotal << std::endl;
        existingPurchase->setPurchasePrice(byHandTotal / newQuant);
    }
    else
    {

        purchases.push_back(purchase);
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
void Portfolio::addPurchaseToPortfolio(Portfolio &portfolio, const Stock &selectedStock, int quantity, float purchasePrice, const Calendar &calendar)
{
    Purchase purchase(selectedStock, quantity, purchasePrice, calendar.getDate());
    portfolio.addPurchase(purchase);
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
Purchase *Portfolio::getPurchase(const std::string &stockSymbol)
{
    for (Purchase &purchase : purchases)
    {
        if (purchase.getStockSymbol() == stockSymbol)
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
