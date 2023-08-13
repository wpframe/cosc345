#include <string>
#include <vector>

// ChatGPTed

struct StockHistory {
    std::string date;
    double closePrice;
};

class Stock {
public:
    Stock(const std::string& symbol, const std::string& name, int outstanding, int ipoYear, const std::string& sector, const std::string& industry);
    std::string symbol;
    std::string name;
    int outstanding;
    int ipoYear;
    std::string sector;
    std::string industry;
    std::vector<StockHistory> history;
    void parseHistory();
};

std::vector<Stock> parseCSV(const std::string& filename);
