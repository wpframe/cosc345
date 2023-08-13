#include "testStocks.h"
#include "Stock.h"
#include <iostream>

testStocks::testStocks() {}

void testStocks::run() {
    std::string filename = "data/nasdaq_screener_filtered.csv";  // Assuming the CSV file is named "stocks.csv"
    std::vector<Stock> stocks = parseCSV(filename);

    for (const Stock& stock : stocks) {
        std::cout << "Symbol: " << stock.symbol;
        std::cout << "\tName: " << stock.name;
        std::cout << "\tOutstanding: " << stock.outstanding;
        std::cout << "\tIPO Year: " << stock.ipoYear;
        std::cout << "\tSector: " << stock.sector;
        std::cout << "\tIndustry: " << stock.industry << std::endl;

        std::cout << "--------------------------" << std::endl;
    }
    
}

