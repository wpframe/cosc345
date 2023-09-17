#ifndef PORTFOLIO_TESTER_H
#define PORTFOLIO_TESTER_H

#include "Portfolio.h"
#include "Stock.h"
#include "Calendar.h"

class PortfolioTester
{
public:
    PortfolioTester();
    int testAddPurchase();
    int testAddShortPurchase();
    int testAddPurchaseFunctionality();
    int testAddShortFunctionality();
    int testGetTotalBalance();
    int testAddMultiplePurchases();
    void runAllTests();
    int testStock();
    int testHeadline();
};

#endif // PORTFOLIO_TESTER_H
