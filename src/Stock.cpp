#include "Stock.h"
#include "Headline.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <ctime>
#include <string>

// ChatGPTed

Stock::Stock(const std::string &symbol, const std::string &name, int outstanding, int ipoYear, const std::string &sector, const std::string &industry)
    : symbol(symbol), name(name), outstanding(outstanding), ipoYear(ipoYear), sector(sector), industry(industry) {}

std::string Stock::getSymbol() const
{
    return symbol;
}

std::string Stock::getName() const
{
    return name;
}

std::vector<Stock> parseCSV(const std::string &filename)
{
    std::vector<Stock> stocks;
    std::ifstream file(filename);

    if (!file.is_open())
    {
        std::cerr << "Failed to open the file: " << filename << std::endl;
        return stocks;
    }

    std::string line;
    // Skip the header line
    std::getline(file, line);

    while (std::getline(file, line))
    {
        std::stringstream ss(line);
        std::string token;

        std::string symbol, name, sector, industry;
        int outstanding = -1, ipoYear = -1;

        std::getline(ss, symbol, ',');
        std::getline(ss, name, ',');

        try
        {
            std::getline(ss, token, ',');
            outstanding = std::stoi(token);
        }
        catch (const std::exception &e)
        {
        }

        try
        {
            std::getline(ss, token, ',');
            ipoYear = std::stoi(token);
        }
        catch (const std::exception &e)
        {
        }

        std::getline(ss, sector, ',');
        std::getline(ss, industry, ',');

        stocks.emplace_back(symbol, name, outstanding, ipoYear, sector, industry);
    }

    file.close();
    return stocks;
}

void Stock::parseHistory()
{
    std::string filename = "data/stocks/" + symbol + ".csv";
    std::ifstream file(filename);

    if (!file.is_open())
    {
        std::cerr << "Failed to open the history file: " << filename << std::endl;
        return;
    }

    std::string line;
    // Skip the header line
    std::getline(file, line);

    while (std::getline(file, line))
    {
        std::stringstream ss(line);
        StockHistory entry;

        std::getline(ss, entry.date, ',');
        std::string closePriceStr;
        std::getline(ss, closePriceStr, ',');
        entry.closePrice = std::stod(closePriceStr);

        history.push_back(entry);
    }

    file.close();
}

std::string getNextDate(const std::string &date)
{
    struct tm tm = {};
    sscanf(date.c_str(), "%d-%d-%d", &tm.tm_year, &tm.tm_mon, &tm.tm_mday);

    // Adjust for tm's year (years since 1900) and month (0-11) representation
    tm.tm_year -= 1900;
    tm.tm_mon -= 1;

    tm.tm_mday += 7; // add 7 days for weekly data

    mktime(&tm); // Normalize the tm structure

    char buffer[11];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d", &tm);
    return std::string(buffer);
}

void Stock::predictNextX(int x) {
    int n = history.size();
    if (n < 2) {
        std::cerr << "Not enough data to predict." << std::endl;
        return;
    }

    // Simple linear regression
    double sumX = 0, sumY = 0, sumXY = 0, sumX2 = 0;
    for (int i = 0; i < n; i++) {
        sumX += i;
        sumY += history[i].closePrice;
        sumXY += i * history[i].closePrice;
        sumX2 += i * i;
    }

    double slope = (n * sumXY - sumX * sumY) / (n * sumX2 - sumX * sumX);
    double intercept = (sumY - slope * sumX) / n;

    for (int i = 0; i < x; i++) {
        std::string nextDate = getNextDate(history.back().date);
        double predictedPrice = slope * (n + i) + intercept;

        // Add randomness
        double randomFactor = 1.0 + (std::rand() % 10 - 5) * 0.01; // Randomness between -5% to +5%
        predictedPrice *= randomFactor;

        // Generate headline and adjust price
        auto headlineEvent = Headline::generateHeadline(*this, n + i);
        predictedPrice *= headlineEvent.second;

        // Ensure the price doesn't go negative
        predictedPrice = std::max(predictedPrice, 0.01);

        history.push_back({nextDate, predictedPrice});
    }
}
