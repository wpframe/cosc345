#include "stock.h"
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>

Stock::Stock(std::string symbol, std::string name, std::string lastSale, std::string netChange,
             std::string percentChange, std::string marketCap, std::string country,
             std::string IPOYear, std::string volume, std::string sector, std::string industry)
    : symbol(symbol), name(name), lastSale(lastSale), netChange(netChange),
      percentChange(percentChange), marketCap(marketCap), country(country),
      IPOYear(IPOYear), volume(volume), sector(sector), industry(industry)
{
}

void Stock::print() const
{
    std::cout << "Symbol: " << symbol << "\nName: " << name << "\nLast Sale: " << lastSale
              << "\nNet Change: " << netChange << "\n% Change: " << percentChange
              << "\nMarket Cap: " << marketCap << "\nCountry: " << country
              << "\nIPO Year: " << IPOYear << "\nVolume: " << volume
              << "\nSector: " << sector << "\nIndustry: " << industry << std::endl;
}

std::vector<Stock> Stock::readStocksFromCSV(const std::string &filename)
{
    std::vector<Stock> stocks;
    std::ifstream fileIn(filename);

    if (!fileIn.is_open())
    {
        // Handle fileIn opening error if needed
        std::cout << "Failed to open file: " << filename << std::endl;
        return stocks;
    }

    std::string line;
    // Skip the header line
    std::getline(fileIn, line);

    while (std::getline(fileIn, line))
    {
        std::istringstream iss(line);
        std::string symbol, name, lastSale, netChange, percentChange,
            marketCap, country, IPOYear, volume, sector, industry;

        // Assuming CSV fields are separated by commas
        std::getline(iss, symbol, ',');
        std::getline(iss, name, ',');
        std::getline(iss, lastSale, ',');
        std::getline(iss, netChange, ',');
        std::getline(iss, percentChange, ',');
        std::getline(iss, marketCap, ',');
        std::getline(iss, country, ',');
        std::getline(iss, IPOYear, ',');
        std::getline(iss, volume, ',');
        std::getline(iss, sector, ',');
        std::getline(iss, industry, ',');

        stocks.emplace_back(symbol, name, lastSale, netChange, percentChange,
                            marketCap, country, IPOYear, volume, sector, industry);
    }

    fileIn.close();
    return stocks;
}
