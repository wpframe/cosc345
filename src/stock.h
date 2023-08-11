#ifndef STOCK_H
#define STOCK_H

#include <string>
#include <vector>

// ChatGPTed

// In stock.h

class Stock
{
public:
    std::string symbol;
    std::string name;
    std::string lastSale;      // New field
    std::string netChange;     // New field
    std::string percentChange; // New field
    std::string marketCap;     // New field
    std::string country;       // New field
    std::string IPOYear;
    std::string volume; // New field
    std::string sector;
    std::string industry;

    Stock(std::string symbol, std::string name, std::string lastSale, std::string netChange,
          std::string percentChange, std::string marketCap, std::string country,
          std::string IPOYear, std::string volume, std::string sector, std::string industry);

    void print() const;

    // static std::vector<Stock> readStocksFromCSV(const std::string &filename);
    static std::vector<Stock> readStocksFromCSV(const std::string &filename);
};

#endif // STOCK_H
