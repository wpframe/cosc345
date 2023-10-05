#ifndef PORTFOLIO_H
#define PORTFOLIO_H

#include "Purchase.h"
#include <vector>
#include "Calendar.h"

class Portfolio
{

private:
    std::vector<Purchase> purchases;
    float totalBalance;

public:
    Portfolio(float initialBalance) : totalBalance(initialBalance) {} // Initialize totalBalance in the constructor
    void addPurchase(Purchase purchase, PositionType holdType);
    void printPortfolio() const;
    Purchase *getPurchase(const std::string &stockSymbol, PositionType holdType);
    float getTotalBalance() const;
    void updateTotalBalance(float amountAdded);
    void resetTotalBalance();
    const std::vector<Purchase> getPurchases() const;
    void summarizePortfolio(int time) const;
    void addPurchaseToPortfolio(Portfolio &portfolio, const Stock &selectedStock, int quantity, float purchasePrice, const Calendar &calendar, const std::string &type);
    void sellPurchase(const Stock &selectedStock, int quantityToSell, float currentPrice, PositionType holdType);
};

extern Portfolio portfolio;
#endif // PORTFOLIO_H
