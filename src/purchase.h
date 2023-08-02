#ifndef PURCHASE_H
#define PURCHASE_H

#include <string>

class Purchase {
private:
    std::string symbol;
    int quantity;
    float price;
public:
    Purchase(std::string symbol, int quantity, float price);
    float getProfit(float currentPrice);
    float getPurchasePrice();
    std::string getSymbol();
    int getQuantity();

};

#endif // STOCK_H