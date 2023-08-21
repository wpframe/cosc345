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

void addPurchaseToPortfolio(Portfolio &portfolio, const Stock &selectedStock, int quantity, float purchasePrice, const Calendar &calendar, float currentPrice)
{
    Purchase purchase(selectedStock, quantity, purchasePrice, calendar.getDate(), currentPrice);
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
