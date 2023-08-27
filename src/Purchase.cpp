/*!
   @file
   @brief The implementation for the Purchase class.
   @details It holds the neccesary information for keeping a record of purchasing a stock.
*/
#pragma once

#include "Purchase.h"
#include "Portfolio.h"
#include "Stock.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

/*!
    @file
    @brief The constructor for the Purchase class.
    @details Takes and initializes the stock, quantity, purchase price, and purchase timestamp.
*/
Purchase::Purchase(const Stock &s, int q, float purchasePrice, const std::string &timestamp)
    : stock(s), quantity(q), purchasePrice(purchasePrice), purchaseTimestamp(timestamp)
{
}

float Purchase::getCurrentPurchaseValue(float currentPrice) const
{
    // float currentPrice = getStock().history[time].closePrice;
    float currentValue = 0.0;
    float currentPurchaseValue = getQuantity() * currentPrice;
    currentValue += currentPurchaseValue;
    return currentValue;
}

float Purchase::getPurchaseValue() const
{
    float purchaseValue = getQuantity() * getPurchasePrice();
    return purchaseValue;
}

float Purchase::getProfitLoss(float currentPrice) const
{
    float profitLoss = getCurrentPurchaseValue(currentPrice) - getPurchaseValue();
    return profitLoss;
}

float Purchase::getProfitLossPercentage(float currentPrice) const
{
    float profitLossPercentage = getProfitLoss(currentPrice) / getPurchaseValue();
    return profitLossPercentage * 100;
}

/*!
    @brief Accessor for the quantity purchased.
    @return The quantity purchased.
*/
int Purchase::getQuantity() const
{
    return quantity;
}

/*!
    @brief Accessor for the purchase price. This is only used in testing.
    @return The purchase price.
*/
float Purchase::getPurchasePrice() const
{
    return purchasePrice;
}

/*!
    @brief Mutator for the stock. This is only used in testing.
    @param s The stock to set.
*/
void Purchase::setStock(const Stock &s)
{
    stock = s;
}

/*!
    @brief Mutator for the quantity purchased. This is only used in testing.
    @param q The quantity purchased.
*/
void Purchase::setQuantity(int q)
{
    quantity = q;
}

/*!
    @brief Accessor for the timestamp of the purchase.
    @return The timestamp of the purchase.
*/
std::string Purchase::getTimeStamp() const
{
    return Purchase::purchaseTimestamp;
}

/*!
    @brief Mutator for the purchase price.
    @param price The purchase price.
*/
void Purchase::setPurchasePrice(float price)
{
    purchasePrice = price;
}

/*!
    @brief Mutator for the current price. This is only used in testing.
    @param price The current price.
*/
void Purchase::setCurrentPrice(float price)
{
    currentPrice = price;
}

/*!
    @brief Mutator for the timestamp of the purchase.
    @param timestamp The timestamp of the purchase.
*/
void Purchase::setTimestamp(const std::string &timestamp)
{
    purchaseTimestamp = timestamp;
}

/*!
    @brief Calculates the total cost of the initial purchase.
    @return The total cost of the initial purchase.
*/
float Purchase::calculateTotalCost() const
{
    return quantity * purchasePrice;
}

/*!
    @brief Calculates the profit of the purchase.
    @return The profit of the purchase.
*/
void Purchase::printPurchaseDetails() const
{
    std::cout << "Stock: " << stock.getName() << " (" << stock.getSymbol() << ")" << std::endl;
    std::cout << "Quantity: " << quantity << std::endl;
    std::cout << "Purchase Price: $" << purchasePrice << std::endl;
    // std::cout << "Total Cost: $" << calculateTotalCost() << std::endl;
    // std::cout << "Purchase Timestamp: " << purchaseTimestamp << std::endl;
}

// This can be removed
std::string Purchase::getStockSymbol() const
{
    return stock.getSymbol();
    // return "aplle";
}

/*!
    @brief Accessor for the stock purchased.
    @return The stock purchased.
*/
Stock Purchase::getStock() const
{
    return stock;
}