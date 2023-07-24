#ifndef STOCK_H
#define STOCK_H

#include <string>

// ChatGPTed

class Stock {
public:
    std::string symbol;
    std::string name;
    std::string counter;
    std::string IPOYear;
    std::string volume;
    std::string sector;
    std::string industry;

    Stock(std::string symbol, std::string name, std::string counter, std::string IPOYear, std::string volume, std::string sector, std::string industry);
    void print();
};

#endif // STOCK_H
