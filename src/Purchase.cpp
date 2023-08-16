#include "Purchase.h"
#include <fstream>
#include <sstream>
#include <iostream>

Purchase::Purchase(const Stock &s, int q, float purchasePrice, const std::string &timestamp, float currentPrice)
    : stock(s), quantity(q), purchasePrice(purchasePrice), purchaseTimestamp(timestamp), currentPrice(currentPrice) {}

int Purchase::getQuantity()
{
    return quantity;
}

void Purchase::setStock(const Stock &s)
{
    stock = s;
}

void Purchase::setQuantity(int q)
{
    quantity = q;
}

std::string Purchase::getTimeStamp() const
{
    return Purchase::purchaseTimestamp;
}
void Purchase::setPurchasePrice(float price)
{
    // purchasePrice = stock.getPriceAtDate(getTimeStamp());
}

void Purchase::setCurrentPrice(float price)
{
    currentPrice = price;
}

void Purchase::setTimestamp(const std::string &timestamp)
{
    purchaseTimestamp = timestamp;
}

float Purchase::calculateProfit() const
{
    return quantity * (currentPrice - purchasePrice);
}

float Purchase::calculateProfitPercentage() const
{
    float profit = quantity * (currentPrice - purchasePrice);
    float initialInvestment = quantity * purchasePrice;

    if (initialInvestment == 0)
    {
        return 0.0f;
    }

    return (profit / initialInvestment) * 100.0f;
}

float Purchase::calculateTotalCost() const
{
    return quantity * purchasePrice;
}

void Purchase::printPurchaseDetails() const
{
    // std::cout << "Stock: " << stock.getName() << " (" << stock.getSymbol() << ")" << std::endl;
    std::cout << "Quantity: " << quantity << std::endl;
    std::cout << "Purchase Price: $" << purchasePrice << std::endl;
    std::cout << "Total Cost: $" << calculateTotalCost() << std::endl;
    std::cout << "Purchase Timestamp: " << purchaseTimestamp << std::endl;
    std::cout << "Current Price: $" << currentPrice << std::endl;
    std::cout << "Total Profit: $" << calculateProfit() << std::endl;
    std::cout << "Total Profit Percentage: " << calculateProfitPercentage() << "%" << std::endl;
}

std::string Purchase::getStockSymbol() const
{
    // return stock.getSymbol();
}

Stock Purchase::getStock() const
{
    return stock;
}
