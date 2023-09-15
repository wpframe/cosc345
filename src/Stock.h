#include <string>
#include <vector>
#ifndef STOCK_H
#define STOCK_H

// ChatGPTed

struct StockHistory
{
    std::string date;
    double closePrice;
    std::string headline;
    double multiplier;
};

class Stock
{
public:
    Stock(const std::string &symbol, const std::string &name, int outstanding, int ipoYear, const std::string &sector, const std::string &industry);
    static Stock updateStockHistory(Stock &selectedStock);
    std::string getSymbol() const;
    std::string getName() const;
    std::string symbol;
    std::string name;
    int outstanding;
    int ipoYear;
    std::string sector;
    std::string industry;
    std::vector<StockHistory> history;
    void parseHistory();
    void predictNextX(int x);
    static Stock findStockBySymbol(const std::string &symbol, const std::vector<Stock> &stocks);
};

std::vector<Stock> parseCSV(const std::string &filename);

#endif // STOCK_H