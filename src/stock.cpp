#include "stock.h"
#include <iostream>

// ChatGPTed

Stock::Stock(std::string symbol, std::string name, std::string counter, std::string IPOYear, std::string volume, std::string sector, std::string industry)
    : symbol(symbol), name(name), counter(counter), IPOYear(IPOYear), volume(volume), sector(sector), industry(industry)
{ }

void Stock::print() {
    std::cout << "Symbol: " << symbol << "\nName: " << name << "\nCounter: " << counter << "\nIPO Year: " << IPOYear << "\nVolume: " << volume << "\nSector: " << sector << "\nIndustry: " << industry << std::endl;
}
