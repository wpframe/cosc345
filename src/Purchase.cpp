/*!
    @file
    @brief The implementation for the Purchase class.
    @details It holds the necessary information for keeping a record of purchasing a stock.
*/

#include "Purchase.h"
#include "Portfolio.h"
#include "Stock.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

/*!
    @brief Constructor for the Purchase class.
    @details Initializes a purchase with the given stock, quantity, purchase price, and timestamp.
    @param s The stock being purchased.
    @param q The quantity being purchased.
    @param purchasePrice The price at which the stock is purchased.
    @param timestamp The timestamp of the purchase.
*/
Purchase::Purchase(const Stock &s, int q, float purchasePrice, const std::string &timestamp)
    : stock(s), quantity(q), purchasePrice(purchasePrice), purchaseTimestamp(timestamp)
{
}

/*!
    @brief Calculates the current value of the purchase.
    @param currentPrice The current price of the stock.
    @return The current value of the purchase.
*/
float Purchase::getCurrentPurchaseValue(float currentPrice) const
{
    float currentValue = 0.0;
    float currentPurchaseValue = getQuantity() * currentPrice;
    currentValue += currentPurchaseValue;
    return currentValue;
}

/*!
    @brief Calculates the initial purchase value.
    @return The initial purchase value.
*/
float Purchase::getPurchaseValue() const
{
    float purchaseValue = getQuantity() * getPurchasePrice();
    return purchaseValue;
}

/*!
    @brief Calculates the profit or loss for the purchase.
    @param currentPrice The current price of the stock.
    @return The profit or loss for the purchase.
*/
float Purchase::getProfitLoss(float currentPrice) const
{
    float profitLoss = getCurrentPurchaseValue(currentPrice) - getPurchaseValue();
    return profitLoss;
}

/*!
    @brief Calculates the profit or loss percentage for the purchase.
    @param currentPrice The current price of the stock.
    @return The profit or loss percentage for the purchase.
*/
float Purchase::getProfitLossPercentage(float currentPrice) const
{
    float profitLossPercentage = (getProfitLoss(currentPrice) / getPurchaseValue()) * 100;
    return profitLossPercentage;
}

/*!
    @brief Accessor for the quantity of stock purchased.
    @return The quantity of stock purchased.
*/
int Purchase::getQuantity() const
{
    return quantity;
}

/*!
    @brief Accessor for the purchase price.
    @return The purchase price.
*/
float Purchase::getPurchasePrice() const
{
    return purchasePrice;
}

/*!
    @brief Mutator for the stock. (For testing purposes)
    @param s The stock to set.
*/
void Purchase::setStock(const Stock &s)
{
    stock = s;
}

/*!
    @brief Mutator for the quantity of stock purchased. (For testing purposes)
    @param q The quantity of stock purchased.
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
    @brief Prints the details of the purchase to the console.
*/
void Purchase::printPurchaseDetails() const
{
    std::cout << "Stock: " << stock.getName() << " (" << stock.getSymbol() << ")" << std::endl;
    std::cout << "Quantity: " << quantity << std::endl;
    std::cout << "Average Purchase Price: $" << purchasePrice << std::endl;
    std::cout << "Total Cost: $" << calculateTotalCost() << std::endl;
    std::cout << "Purchase Timestamp: " << purchaseTimestamp << std::endl;
}

/*!
    @brief Accessor for the stock of the purchase.
    @return The stock of the purchase.
*/
Stock Purchase::getStock() const
{
    return stock;
}
