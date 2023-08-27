#ifndef PORTFOLIO_TESTER_H
#define PORTFOLIO_TESTER_H

#include "Portfolio.h"
#include "Stock.h"
#include "Calendar.h"

class PortfolioTester
{
public:
    PortfolioTester();
    void testAddPurchase();
    void testAddPurchaseFunctionality();
    void testGetTotalBalance();
    void testAddMultiplePurchases();
    void runAllTests();
};

#endif // PORTFOLIO_TESTER_H
