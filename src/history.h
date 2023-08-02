#ifndef HISTORY_H
#define HISTORY_H

#include <string>
#include <vector>

class History {
private:
    std::string symbol;
    std::vector<float> history;
public:
    History(std::string symbol, std::vector<float> history);
    void initialiseHistory();
    std::vector<float> getHistory();
    static History& findBySymbol(const std::string& symbol);

};

#endif // STOCK_H