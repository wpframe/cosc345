#include "Portfolio.h"
#include <iostream>
#include "Calendar.h"

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

void Portfolio::addPurchaseToPortfolio(Portfolio &portfolio, const Stock &selectedStock, int quantity, float purchasePrice, const Calendar &calendar)
{
    Purchase purchase(selectedStock, quantity, purchasePrice, calendar.getDate());
    portfolio.addPurchase(purchase);
}

void Portfolio::printPortfolio() const
{
    std::cout << "Portfolio Details:" << std::endl;
    for (const Purchase &purchase : purchases)
    {
        std::cout << "------------------------------" << std::endl;
        purchase.printPurchaseDetails();
    }
}

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

const std::vector<Purchase> Portfolio::getPurchases() const
{
    return purchases;
}

void Portfolio::summarizePortfolio(int time) const
{
    float totalInvestment = 0.0;
    float currentValue = 0.0;

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
