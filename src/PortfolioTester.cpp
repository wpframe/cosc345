/**
 * @file PortfolioTester.cpp
 * @brief Implementation of PortfolioTester class for testing Portfolio functionality.
 */

#include <iostream>
#include "Portfolio.h"
#include "Stock.h"
#include "Calendar.h"
#include "PortfolioTester.h"
#include "Purchase.h"
#include "Headline.h"

/**
 * @brief Default constructor for PortfolioTester class.
 */
PortfolioTester::PortfolioTester() {}

/**
 * @brief Test the functionality of adding a single purchase to the portfolio.
 */
int PortfolioTester::testAddPurchase()
{
    std::cout << "TESTING ADDING PURCHASE FUNCTIONALITY" << std::endl;
    Calendar calendar;
    Portfolio portfolio(100000);
    Stock testStock("AAPL", "Apple Inc.", 1000000, 1980, "Technology", "Consumer Electronics");
    PositionType holdingType = PositionType::Long;
    std::string holdingTypeStr = "Long";

    portfolio.addPurchaseToPortfolio(portfolio, testStock, 10, 150.0, calendar, holdingTypeStr);

    Purchase *purchase = portfolio.getPurchase("AAPL", holdingType);

    purchase->printPurchaseDetails();
    std::cout << "Total Cost of Purchase: " << purchase->getQuantity() << " * " << purchase->getPurchasePrice() << " = " << purchase->getQuantity() * purchase->getPurchasePrice() << std::endl;

    if (purchase->getPurchasePrice() == 150.0 && purchase->getQuantity() == 10 && purchase->getQuantity() * purchase->getPurchasePrice() == 150.0 * 10)
    {
        std::cout << "Test Passed: Purchase price, quantity and total cost are correct." << std::endl;
        std::cout << "#######################################################" << std::endl;
        return 0;
    }
    else
    {
        std::cout << "Test Failed" << std::endl;
        std::cout << "#######################################################" << std::endl;
        return 1;
    }
}

/**
 * @brief Test stock functionality.
 */
int PortfolioTester::testStock()
{
    std::string ticker = "AAPL";
    std::string name = "Apple Inc.";
    int marketCap = 1000000000;
    int yearFounded = 1980;
    std::string sector = "Technology";
    std::string industry = "Consumer Electronics";
    Stock x = Stock(ticker, name, marketCap, yearFounded, sector, industry);
    std::cout << "TESTING STOCK FUNCTIONALITY" << std::endl;
    bool flag = false;
    try
    {
        x.parseHistory();
    }
    catch (const std::exception &e)
    {
        flag = true;
    }
    if (x.getName() != name)
    {
        flag = true;
    }
    if (x.getSymbol() != ticker)
    {
        flag = true;
    }

    if (flag == false)
    {
        std::cout << "Test Passed: Stock was correctly created." << std::endl;
        std::cout << "#######################################################" << std::endl;
        return 0;
    }
    else
    {
        std::cout << "Test Failed" << std::endl;
        std::cout << "#######################################################" << std::endl;
        return 1;
    }
}

/**
 * @brief Test headline functionality.
 */
int PortfolioTester::testHeadline()
{
    try
    {
        Headline::readFromCSV("data/headlines.csv");
    }
    catch (const std::exception &e)
    {
        std::cout << "Reading from CSV Failed" << std::endl;
        std::cout << "#######################################################" << std::endl;
        return 1;
    }

    try
    {
        Stock x = Stock("AAPL", "Apple Inc.", 1000000000, 1980, "Technology", "Consumer Electronics");
        int seed = 112513251;
        for (int i = 0; i < 52; i++)
        {
            Headline::generateHeadline(x, seed++);
        }
    }
    catch (const std::exception &e)
    {
        std::cout << "Generating Headline Failed" << std::endl;
        std::cout << "#######################################################" << std::endl;
        return 1;
    }

    std::cout << "Test Passed: Headlines were correctly generated." << std::endl;
    std::cout << "#######################################################" << std::endl;
    return 0;
}

/**
 * @brief Test the functionality of adding purchases of the same stock to the portfolio.
 */
int PortfolioTester::testAddPurchaseFunctionality()
{
    std::cout << "TESTING ADDING PURCHASE OF SAME STOCK FUNCTIONALITY" << std::endl;
    Calendar calendar;
    Portfolio portfolio(100000);
    PositionType holdingType = PositionType::Long;
    std::string holdingTypeStr = "Long";

    Stock testStock("AAPL", "Apple Inc.", 1000000, 1980, "Technology", "Consumer Electronics");

    portfolio.addPurchaseToPortfolio(portfolio, testStock, 10, 150.0, calendar, holdingTypeStr);
    portfolio.addPurchaseToPortfolio(portfolio, testStock, 5, 160.0, calendar, holdingTypeStr);

    Purchase *addedPurchase = portfolio.getPurchase("AAPL", holdingType);

    if (addedPurchase)
    {
        int expectedTotalQuantity = 10 + 5;
        float expectedTotalCost = 10 * 150.0 + 5 * 160.0;
        float expectedAveragePrice = expectedTotalCost / expectedTotalQuantity;

        std::cout << "Expected Total Quantity: " << expectedTotalQuantity << std::endl;
        std::cout << "Expected Total Cost: " << expectedTotalCost << std::endl;
        std::cout << "Expected Average Price: " << expectedAveragePrice << std::endl;

        std::cout << "Added Purchase Quantity: " << addedPurchase->getQuantity() << std::endl;
        std::cout << "Added Purchase Average Price: " << addedPurchase->getPurchasePrice() << std::endl;
        std::cout << "Added Purchase Total Cost: " << addedPurchase->getQuantity() * addedPurchase->getPurchasePrice() << std::endl;

        if (addedPurchase->getQuantity() == expectedTotalQuantity &&
            addedPurchase->getPurchasePrice() == expectedAveragePrice)
        {
            std::cout << "Test Passed: Purchases were correctly added and updated." << std::endl;
            std::cout << "#######################################################" << std::endl;
            return 0;
        }
        else
        {
            std::cout << "Test Failed: Purchases were not updated correctly." << std::endl;
            std::cout << "#######################################################" << std::endl;
            return 1;
        }
    }
    else
    {
        std::cout << "Test Failed: Unable to retrieve added purchase." << std::endl;
        std::cout << "#######################################################" << std::endl;
        return 1;
    }
}

/**
 * @brief Test the functionality of calculating the total balance of the portfolio.
 */
int PortfolioTester::testGetTotalBalance()
{
    std::cout << "TESTING TOTAL BALANCE FUNCTIONALITY" << std::endl;
    Calendar calendar;
    Portfolio portfolio(100000);
    PositionType holdingType = PositionType::Long;
    std::string holdingTypeStr = "Long";
    std::cout << "Starting Total Balance: " << portfolio.getTotalBalance() << std::endl;
    Stock testStock("AAPL", "Apple Inc.", 1000000, 1980, "Technology", "Consumer Electronics");
    portfolio.addPurchaseToPortfolio(portfolio, testStock, 10, 150.0, calendar, holdingTypeStr);
    portfolio.addPurchaseToPortfolio(portfolio, testStock, 5, 160.0, calendar, holdingTypeStr);

    Purchase *purchase = portfolio.getPurchase("AAPL", holdingType);

    float totalPurchaseCost = purchase->calculateTotalCost();

    float totalBalance = portfolio.getTotalBalance();

    float expectedTotalBalance = 100000 - (10 * 150.0 + 5 * 160.0);
    std::cout << "Total Cost of Purchase: " << totalPurchaseCost << std::endl;
    std::cout << "Expected Total Balance: " << expectedTotalBalance << std::endl;
    std::cout << "Calculated Total Balance: " << totalBalance << std::endl;

    if (totalBalance == expectedTotalBalance)
    {
        std::cout << "Test Passed: Total balance calculated correctly." << std::endl;
        std::cout << "#######################################################" << std::endl;
        return 0;
    }
    else
    {
        std::cout << "Test Failed: Total balance calculation is incorrect." << std::endl;
        std::cout << "#######################################################" << std::endl;
        return 1;
    }
}

/**
 * @brief Test adding multiple purchases to the portfolio.
 */
int PortfolioTester::testAddMultiplePurchases()
{
    std::cout << "TESTING ADDING MULTIPLE PURCHASES FUNCTIONALITY" << std::endl;
    Calendar calendar;
    Portfolio portfolio(1000000);
    PositionType holdingType = PositionType::Long;
    std::string holdingTypeStr = "Long";

    Stock stock1("AAPL", "Apple Inc.", 1000000, 1980, "Technology", "Consumer Electronics");
    Stock stock2("GOOGL", "Alphabet Inc.", 1500000, 1998, "Technology", "Internet Services");
    Stock stock3("MSFT", "Microsoft Corporation", 2000000, 1975, "Technology", "Software");
    Stock stock4("AMZN", "Amazon.com Inc.", 1800000, 1994, "Retail", "E-Commerce");
    Stock stock5("TSLA", "Tesla Inc.", 900000, 2003, "Automotive", "Electric Vehicles");

    portfolio.addPurchaseToPortfolio(portfolio, stock1, 10, 150.0, calendar, holdingTypeStr);
    portfolio.addPurchaseToPortfolio(portfolio, stock2, 20, 250.0, calendar, holdingTypeStr);
    portfolio.addPurchaseToPortfolio(portfolio, stock3, 5, 300.0, calendar, holdingTypeStr);
    portfolio.addPurchaseToPortfolio(portfolio, stock4, 15, 1800.0, calendar, holdingTypeStr);
    portfolio.addPurchaseToPortfolio(portfolio, stock5, 8, 650.0, calendar, holdingTypeStr);

    bool allPurchasesAddedCorrectly = true;
    for (const Purchase &purchase : portfolio.getPurchases())
    {
        purchase.printPurchaseDetails();
    }

    int expectedTotalPurchases = 5;

    int actualTotalPurchases = portfolio.getPurchases().size();

    if (actualTotalPurchases == expectedTotalPurchases)
    {
        std::cout << "Test Passed: All purchases were added correctly." << std::endl;
        std::cout << "#######################################################" << std::endl;
        return 0;
    }
    else
    {
        std::cout << "Test Failed: Some purchases were not added correctly." << std::endl;
        std::cout << "#######################################################" << std::endl;
        return 1;
    }
}

/**
 * @brief Run all the test methods of the PortfolioTester class.
 */
void PortfolioTester::runAllTests()
{
    std::cout << "Running Portfolio Tests..." << std::endl;
    int failedCount = 0;
    failedCount += testAddPurchase();
    failedCount += testAddPurchaseFunctionality();
    failedCount += testGetTotalBalance();
    failedCount += testAddMultiplePurchases();
    failedCount += testStock();
    failedCount += testHeadline();
    if (failedCount == 0)
    {
        std::cout << "All Tests Passed!" << std::endl;
    }
    else
    {
        std::cout << failedCount << " Tests Failed!" << std::endl;
    }
}
