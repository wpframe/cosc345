#include "testStocks.h"
#include "Stock.h"
#include <iostream>

// TEMPORARY TEST APP 

testStocks::testStocks() {}

void testStocks::run() {
    std::string filename = "data/nasdaq_screener_filtered.csv";  // Assuming the CSV file is named "stocks.csv"
    std::vector<Stock> stocks = parseCSV(filename);

    for (Stock& stock : stocks) {
        stock.parseHistory();
        // call the predictNextX function on the current stock.
        stock.predictNextX(5200);
        

        std::cout << "Date,Close";
        const auto& history = stock.history;
        for (const auto& entry : history) {
            std::cout << entry.date << "," << entry.closePrice << std::endl;
        }
        return;

        // std::cout << "--------------------------" << std::endl;

        // std::cout << "Symbol: " << stock.symbol;
        // std::cout << "\tName: " << stock.name;
        // std::cout << "\tOutstanding: " << stock.outstanding;
        // std::cout << "\tIPO Year: " << stock.ipoYear;
        // std::cout << "\tSector: " << stock.sector;
        // std::cout << "\tIndustry: " << stock.industry << std::endl;

        // std::cout << "--------------------------" << std::endl;

        // stock.parseHistory();
        // const auto& history = stock.history;
        // for (const auto& entry : history) {
        //     std::cout << "Date: " << entry.date << ", Close Price: " << entry.closePrice << std::endl;
        // }
    }

    
}

