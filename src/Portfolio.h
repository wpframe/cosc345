#ifndef PORTFOLIO_H
#define PORTFOLIO_H

#include "Purchase.h"
#include <vector>

class Portfolio
{
private:
    std::vector<Purchase> purchases;

public:
    void replacePurchase(const Purchase &newPurchase);
    void addPurchase(Purchase purchase);
    void updatePricesAndProfits();
    void printPortfolio() const;
    Purchase *getPurchase(const std::string &stockSymbol);
    const std::vector<Purchase> getPurchases() const;
};

#endif // PORTFOLIO_H
