#include "Stock.h"
#ifndef PURCHASE_H
#define PURCHASE_H

enum class PositionType
{
    Long,
    Short
};

class Purchase
{
private:
    Stock stock;
    int quantity;
    float purchasePrice;
    float currentPrice;
    std::string purchaseTimestamp;
    std::string purchaseType;
    PositionType holdType;

public:
    Purchase(const Stock &s, int q, float purchasePrice, const std::string &timestamp, PositionType holdType);

    // void makePurchase(const Stock &s, int q, float purchasePrice);
    void setStock(const Stock &s);
    void setQuantity(int q);
    void setPurchasePrice(float price);
    void setCurrentPrice(float price);
    void setTimestamp(const std::string &timestamp);

    std::string getTimeStamp() const;
    std::string getStockSymbol() const;
    Stock getStock() const;
    int getQuantity() const;
    float getCurrentPurchaseValue() const;
    float getCurrentPurchaseValue(float currentPrice) const;
    float getPurchaseValue() const;
    float getPurchasePrice() const;
    float getProfitLoss(float currentPrice) const;
    PositionType getPositionType() const;
    float getProfitLossPercentage(float currentPrice) const;

    float calculateTotalCost() const;
    void printPurchaseDetails() const;
};

#endif
