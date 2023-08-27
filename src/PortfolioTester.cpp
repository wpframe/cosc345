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

/**
 * @brief Default constructor for PortfolioTester class.
 */
PortfolioTester::PortfolioTester() {}

/**
 * @brief Test the functionality of adding a single purchase to the portfolio.
 */
void PortfolioTester::testAddPurchase()
{
    std::cout << "TESTING ADDING PURCHASE FUNCTIONALITY" << std::endl;
    Calendar calendar;
    Portfolio portfolio(100000);
    Stock testStock("AAPL", "Apple Inc.", 1000000, 1980, "Technology", "Consumer Electronics");

    portfolio.addPurchaseToPortfolio(portfolio, testStock, 10, 150.0, calendar);

    Purchase *purchase = portfolio.getPurchase("AAPL");

    purchase->printPurchaseDetails();
    std::cout << "Total Cost of Purchase: " << purchase->getQuantity() << " * " << purchase->getPurchasePrice() << " = " << purchase->getQuantity() * purchase->getPurchasePrice() << std::endl;

    if (purchase->getPurchasePrice() == 150.0 && purchase->getQuantity() == 10 && purchase->getQuantity() * purchase->getPurchasePrice() == 150.0 * 10)
    {
        std::cout << "Test Passed: Purchase price, quantity and total cost are correct." << std::endl;
    }
    else
    {
        std::cout << "Test Failed" << std::endl;
    }
    std::cout << "#######################################################" << std::endl;
}

/**
 * @brief Test the functionality of adding purchases of the same stock to the portfolio.
 */
void PortfolioTester::testAddPurchaseFunctionality()
{
    std::cout << "TESTING ADDING PURCHASE OF SAME STOCK FUNCTIONALITY" << std::endl;
    Calendar calendar;
    Portfolio portfolio(100000);

    Stock testStock("AAPL", "Apple Inc.", 1000000, 1980, "Technology", "Consumer Electronics");

    portfolio.addPurchaseToPortfolio(portfolio, testStock, 10, 150.0, calendar);
    portfolio.addPurchaseToPortfolio(portfolio, testStock, 5, 160.0, calendar);

    Purchase *addedPurchase = portfolio.getPurchase("AAPL");

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
        }
        else
        {
            std::cout << "Test Failed: Purchases were not updated correctly." << std::endl;
        }
    }
    else
    {
        std::cout << "Test Failed: Unable to retrieve added purchase." << std::endl;
    }
    std::cout << "#######################################################" << std::endl;
}

/**
 * @brief Test the functionality of calculating the total balance of the portfolio.
 */
void PortfolioTester::testGetTotalBalance()
{
    std::cout << "TESTING TOTAL BALANCE FUNCTIONALITY" << std::endl;
    Calendar calendar;
    Portfolio portfolio(100000);
    std::cout << "Starting Total Balance: " << portfolio.getTotalBalance() << std::endl;
    Stock testStock("AAPL", "Apple Inc.", 1000000, 1980, "Technology", "Consumer Electronics");
    portfolio.addPurchaseToPortfolio(portfolio, testStock, 10, 150.0, calendar);
    portfolio.addPurchaseToPortfolio(portfolio, testStock, 5, 160.0, calendar);

    Purchase *purchase = portfolio.getPurchase("AAPL");

    float totalPurchaseCost = purchase->calculateTotalCost();

    float totalBalance = portfolio.getTotalBalance();

    float expectedTotalBalance = 100000 - (10 * 150.0 + 5 * 160.0);
    std::cout << "Total Cost of Purchase: " << totalPurchaseCost << std::endl;
    std::cout << "Expected Total Balance: " << expectedTotalBalance << std::endl;
    std::cout << "Calculated Total Balance: " << totalBalance << std::endl;

    if (totalBalance == expectedTotalBalance)
    {
        std::cout << "Test Passed: Total balance calculated correctly." << std::endl;
    }
    else
    {
        std::cout << "Test Failed: Total balance calculation is incorrect." << std::endl;
    }
    std::cout << "#######################################################" << std::endl;
}

/**
 * @brief Test adding multiple purchases to the portfolio.
 */
void PortfolioTester::testAddMultiplePurchases()
{
    std::cout << "TESTING ADDING MULTIPLE PURCHASES FUNCTIONALITY" << std::endl;
    Calendar calendar;
    Portfolio portfolio(1000000);

    Stock stock1("AAPL", "Apple Inc.", 1000000, 1980, "Technology", "Consumer Electronics");
    Stock stock2("GOOGL", "Alphabet Inc.", 1500000, 1998, "Technology", "Internet Services");
    Stock stock3("MSFT", "Microsoft Corporation", 2000000, 1975, "Technology", "Software");
    Stock stock4("AMZN", "Amazon.com Inc.", 1800000, 1994, "Retail", "E-Commerce");
    Stock stock5("TSLA", "Tesla Inc.", 900000, 2003, "Automotive", "Electric Vehicles");

    portfolio.addPurchaseToPortfolio(portfolio, stock1, 10, 150.0, calendar);
    portfolio.addPurchaseToPortfolio(portfolio, stock2, 20, 250.0, calendar);
    portfolio.addPurchaseToPortfolio(portfolio, stock3, 5, 300.0, calendar);
    portfolio.addPurchaseToPortfolio(portfolio, stock4, 15, 1800.0, calendar);
    portfolio.addPurchaseToPortfolio(portfolio, stock5, 8, 650.0, calendar);

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
    }
    else
    {
        std::cout << "Test Failed: Some purchases were not added correctly." << std::endl;
    }
    std::cout << "#######################################################" << std::endl;
}

/**
 * @brief Run all the test methods of the PortfolioTester class.
 */
void PortfolioTester::runAllTests()
{
    std::cout << "Running Portfolio Tests..." << std::endl;
    testAddPurchase();
    testAddPurchaseFunctionality();
    testGetTotalBalance();
    testAddMultiplePurchases();
    std::cout << "All Portfolio Tests Passed!" << std::endl;
}
