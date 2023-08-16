#include "Portfolio.h"
#include <iostream>

void Portfolio::addPurchase(Purchase purchase)
{
    Purchase *existingPurchase = getPurchase(purchase.getStockSymbol());

    if (existingPurchase)
    {

        existingPurchase->setQuantity(existingPurchase->getQuantity() + purchase.getQuantity());
        // existingPurchase->updatePurchasePrice(purchase.getStock.getPrice());
    }
    else
    {

        purchases.push_back(purchase);
    }
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
