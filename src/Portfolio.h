#ifndef PORTFOLIO_H
#define PORTFOLIO_H

#include "Purchase.h"
#include <vector>
#include "Calendar.h"

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
    void addPurchaseToPortfolio(Portfolio &portfolio, const Stock &selectedStock, int quantity, float purchasePrice, const Calendar &calendar, float currentPrice);
};

#endif // PORTFOLIO_H
