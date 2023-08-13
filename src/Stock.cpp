#include "Stock.h"
#include <fstream>
#include <sstream>
#include <iostream>

// ChatGPTed

Stock::Stock(const std::string& symbol, const std::string& name, int outstanding, int ipoYear, const std::string& sector, const std::string& industry)
    : symbol(symbol), name(name), outstanding(outstanding), ipoYear(ipoYear), sector(sector), industry(industry) {}

std::vector<Stock> parseCSV(const std::string& filename) {
    std::vector<Stock> stocks;
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Failed to open the file: " << filename << std::endl;
        return stocks;
    }

    std::string line;
    // Skip the header line
    std::getline(file, line);

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string token;

        std::string symbol, name, sector, industry;
        int outstanding = -1, ipoYear = -1;

        std::getline(ss, symbol, ',');
        std::getline(ss, name, ',');
        
        try {
            std::getline(ss, token, ',');
            outstanding = std::stoi(token);
        } catch (const std::exception& e) {}

        try {
            std::getline(ss, token, ',');
            ipoYear = std::stoi(token);
        } catch (const std::exception& e) {}

        std::getline(ss, sector, ',');
        std::getline(ss, industry, ',');

        stocks.emplace_back(symbol, name, outstanding, ipoYear, sector, industry);
    }

    file.close();
    return stocks;
}
