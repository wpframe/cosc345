#pragma once
#include "Stock.h"

class Purchase
{
private:
    Stock stock;
    int quantity;
    float purchasePrice;
    float currentPrice;
    std::string purchaseTimestamp;

public:
    Purchase(const Stock &s, int q, float purchasePrice, const std::string &timestamp, float currentPrice);

    void setStock(const Stock &s);
    void setQuantity(int q);
    void setPurchasePrice(float price);
    void setCurrentPrice(float price);
    void setTimestamp(const std::string &timestamp);

    std::string getTimeStamp() const;
    std::string getStockSymbol() const;
    Stock getStock() const;
    int getQuantity();

    float calculateProfit() const;
    float calculateProfitPercentage() const;
    float calculateTotalCost() const;
    void printPurchaseDetails() const;
};
