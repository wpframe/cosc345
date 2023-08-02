#include "purchase.h"


// Assisted by ChatGPT
class Purchase {

private:

    std::string symbol;
    int quantity;
    float price;

public:

    Purchase::Purchase(std::string symbol, int quantity, float price)
        : symbol(symbol), quantity(quantity), price(price)
    { }


    float stock::getProfit(float currentPrice) {
        return quantity * (currentPrice - price);
    }

    float getPurchasePrice() {
        return price;
    }

    std::string getSymbol() {
        return symbol;
    }

    int getQuantity() {
        return quantity;
    }
};