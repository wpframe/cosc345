/*!
   @file
   @brief The implementation for the Purchase class.
   @details It holds the neccesary information for keeping a record of purchasing a stock.
*/

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
Purchase::Purchase(const Stock &s, int q, float purchasePrice, const std::string &timestamp, PositionType holdType)
    : stock(s), quantity(q), purchasePrice(purchasePrice), purchaseTimestamp(timestamp), holdType(holdType)
{
}

/*!
    @brief Accessor for the hold type of the purchase
    @return holdType.
*/
PositionType Purchase::getPositionType() const
{
    return holdType;
}

/*!
    @brief Calculates current value of stocks owned for given purchase.
    @param currentPrice the current price of the stock.
    @return The value of a number of a given stock.
*/
float Purchase::getCurrentPurchaseValue(float currentPrice) const
{
    float currentValue = 0.0;

    float currentPurchaseValue;
    if (holdType == PositionType::Long)
    {
        currentPurchaseValue = getQuantity() * currentPrice;
    }
    else
    {
        currentPurchaseValue = getQuantity() * getPurchasePrice() - getQuantity() * currentPrice;
    }
    // For a long position, calculate normally
    currentValue += currentPurchaseValue;

    // For a short position, calculate the value of the borrowed shares
    // minus the value of repurchased shares

    return currentValue;
}

/*!
    @brief Calculates the total value of the purchase for when the purchase was made.
    @return The value of the purchase.
*/
float Purchase::getPurchaseValue() const
{
    float purchaseValue;
    if (holdType == PositionType::Long)
    {
        purchaseValue = getQuantity() * getPurchasePrice();
    }
    else
    {
        purchaseValue = 0.0;
    }
    return purchaseValue;
}

/*!
    @brief Calculates profit or loss.
    @details calculates profit or loss after checking whether the position type is a long or short.
    @param currentPrice the current price of the stock.
    @return The profit or loss at current time.
*/
float Purchase::getProfitLoss(float currentPrice) const
{

    float profitLoss = getCurrentPurchaseValue(currentPrice) - getPurchaseValue();

    // float profitLoss = 0.0;
    // if (holdType == PositionType::Long)
    // {
    //     // For a long position, calculate normally
    //     profitLoss = getCurrentPurchaseValue(currentPrice) - getPurchaseValue();
    // }
    // else
    // {
    //     // For a short position, calculate the value of the borrowed shares
    //     // minus the value of repurchased shares
    //     profitLoss = getPurchaseValue() - getCurrentPurchaseValue(currentPrice);
    // }

    return profitLoss;
}

/*!
    @brief gets the percentage gained or lost based on profit and loss.
    @param currentPrice the current price of the stock.
    @return profit/loss as a percentage.
*/
float Purchase::getProfitLossPercentage(float currentPrice) const
{
    float profitLossPercentage;

    if (holdType == PositionType::Long)
    {
        profitLossPercentage = (currentPrice - getPurchasePrice()) / getPurchasePrice();
    }
    else
    {
        profitLossPercentage = (getPurchasePrice() - currentPrice) / getPurchasePrice();
    }
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

std::string Purchase::getStockSymbol() const
{
    return stock.getSymbol();
}

/*!
    @brief Accessor for the stock purchased.
    @return The stock purchased.
*/
Stock Purchase::getStock() const
{
    return stock;
}