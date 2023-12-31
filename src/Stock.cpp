/*!
    @file
    @brief The implementation for the Stock class.
    @details It holds the neccesary information for each stock, most importantly its symbol, name, and history.
*/

#include "Stock.h"
#include "Headline.h"
#include "PathUtil.h"
#include "Calendar.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <ctime>
#include <string>
#include <cmath>

/*!
    @brief The constructor for the Stock class.
    @details Takes and initializes the symbol, name, outstanding shares, IPO year, sector, and industry.
    @param symbol The stock's symbol.
    @param name The stock's name.
    @param outstanding The stock's outstanding shares.
    @param ipoYear The stock's IPO year.
    @param sector The stock's sector.
    @param industry The stock's industry.
*/

Stock::Stock(const std::string &symbol, const std::string &name, int outstanding, int ipoYear, const std::string &sector, const std::string &industry)
    : symbol(symbol), name(name), outstanding(outstanding), ipoYear(ipoYear), sector(sector), industry(industry) {}

/*!
    @brief Updates the history of a given stock
    @param selectedStock the selected stock
    @return The stock.
*/
Stock Stock::updateStockHistory(Stock &selectedStock)
{
    if (selectedStock.history.size() < 1)
    {
        selectedStock.parseHistory();
        selectedStock.predictNextX(5772);
    }

    return selectedStock;
}

/*!
    @brief Searches for a stock based on the given symbol.
    @param symbol the stock symbol to search with
    @param stocks the vector of all stocks
    @return The stock.
*/
Stock Stock::findStockBySymbol(const std::string &symbol, const std::vector<Stock> &stocks)
{
    for (const Stock &stock : stocks)
    {
        if (stock.symbol == symbol)
        {
            return stock;
        }
    }
    // Return a default Stock or throw an exception if not found
    return Stock("", "", 0, 0, "", "");
}

/*!
    @brief Accessor for the stock's symbol.
    @return The stock's symbol.
*/
std::string Stock::getSymbol() const
{
    return symbol;
}

/*!
    @brief Accessor for the stock's name.
    @return The stock's name.
*/
std::string Stock::getName() const
{
    return name;
}

/*!
    @brief Parses a CSV file (the screener) containing information about all stocks.
    @details It adds all of the stocks in the file to a vector called stocks.
    @param filename The name of the file to parse.
    @return A vector containing all of the stocks in the file.
*/
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

/*!
    @brief Parses a directory of CSV files containing stock history data.
    @details It adds all of the stock history in the files to a vector called history for the current stock.
*/
void Stock::parseHistory()
{
    std::string prefix = PathUtil::findPathFromApp();
    std::string filename = prefix + "src/data/stocks/" + symbol + ".csv";
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
        entry.headline = "";
        entry.multiplier = 1;

        history.push_back(entry);
    }

    file.close();
}

/*!
    @brief A function used to get the next date from a given date.
    @details The new date will be 7 days after the given date.
    @param date The given date.
    @return The new date.
*/
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

/*!
    @brief Predicts the next number of weeks of stock prices for the current stock.
    @details It uses the stock's history to predict the next number of weeks of stock prices.
    @param x The number of weeks to predict.
*/
template <typename T>
T clamp(const T &val, const T &min, const T &max)
{
    return std::max(min, std::min(val, max));
}

void Stock::predictNextX(int numWeeks)
{
    int n = history.size();
    if (n < 2)
    {
        std::cerr << "Not enough data to predict for stock: " << symbol << std::endl;
        return;
    }

    // Simple linear regression for initial trend
    double sumX = 0, sumY = 0, sumXY = 0, sumX2 = 0;
    for (int i = 0; i < n; i++)
    {
        sumX += i;
        sumY += history[i].closePrice;
        sumXY += i * history[i].closePrice;
        sumX2 += i * i;
    }

    double slope = (n * sumXY - sumX * sumY) / (n * sumX2 - sumX * sumX);
    double intercept = (sumY - slope * sumX) / n;

    double momentum = 1.0; // Start with neutral momentum

    for (int i = 0; i < numWeeks; i++)
    {
        StockHistory historyPlusHeadline;

        std::string nextDate = getNextDate(history.back().date);
        double predictedPrice = slope * (n + i) + intercept;

        // Add randomness
        double randomFactor = 1.0 + (std::rand() % 20 - 10) * 0.01; // Randomness between -10% to +10%
        predictedPrice *= randomFactor;

        // Adjust for momentum
        if (randomFactor > 1.0)
            momentum += 0.01; // Increase momentum if stock went up
        else if (randomFactor < 1.0)
            momentum -= 0.01; // Decrease momentum if stock went down

        momentum = clamp(momentum, 0.95, 1.05); // Limit momentum between -5% and +5%
        predictedPrice *= momentum;

        // Generate headline and adjust price
        auto headlineEvent = Headline::generateHeadline(*this, n + i);
        predictedPrice *= headlineEvent.second;

        // Ensure the price doesn't go negative
        predictedPrice = std::max(predictedPrice, 0.01);

        historyPlusHeadline.date = nextDate;
        historyPlusHeadline.closePrice = predictedPrice;
        historyPlusHeadline.headline = headlineEvent.first;
        historyPlusHeadline.multiplier = headlineEvent.second;

        if (i + 1 < history.size())
        {
            history[i].date = historyPlusHeadline.date;
            history[i].closePrice = historyPlusHeadline.closePrice;
            history[i].headline = historyPlusHeadline.headline;
            history[i].multiplier = historyPlusHeadline.multiplier;
        }
        else
        {
            history.push_back(historyPlusHeadline);
        }
    }
}

/*!
    @brief A function used to write the histories to a csv
    @param symbol the stock ticker
    @param StockHistory the history for a given stock
    @param currentDate the current in game date
*/
void Stock::writeToCSV(std::string symbol, const std::vector<StockHistory> &histories, std::string currentDate)
{
    std::string prefix = PathUtil::findPathFromApp();
    std::string filename = prefix + "src/data/stocks/" + symbol + ".csv";
    std::ifstream inputFile(filename);

    std::string outputFilename = prefix + "assets/data/stocks/" + symbol + ".csv";
    std::ofstream outFile(outputFilename);

    if (!outFile)
    {
        std::cerr << "Error opening file for writing history";
        return;
    }

    // Write the header
    outFile << "Date,Open,High,Low,Close,Volume\n";

    std::string line;
    bool isFirstLine = true; // Flag to identify the first line

    while (std::getline(inputFile, line))
    {
        // Check if it's the first line and if it's the header line
        if (isFirstLine && line == "Date,Open,High,Low,Close,Volume")
        {
            isFirstLine = false; // Skip the first line
            continue;
        }

        outFile << line << "\n";
    }

    std::string lastDate;
    for (const auto &history : histories)
    {
        if (history.date == lastDate)
        {
            continue;
        }
        lastDate = history.date;
        // History date is in the past
        outFile << history.date << ",";
        outFile << "0,"; // Open
        outFile << "0,"; // High
        outFile << "0,"; // Low
        outFile << history.closePrice << ",";
        outFile << "0\n"; // Volume
    }

    // Close both files
    inputFile.close();
    outFile.close();
}
// void Stock::writeToCSV(std::string symbol, const std::vector<StockHistory> &histories, std::string currentDate)
// {
//     std::cout << "marker 1" << std::endl;
//     std::string prefix = PathUtil::findPathFromApp();
//     std::string filename = prefix + "src/data/stocks/" + symbol + ".csv";
//     std::ifstream inputFile(filename);
//     std::cout << "input path: " << filename << std::endl;

//     std::string outputFilename = prefix + "assets/data/stocks/" + symbol + ".csv";
//     std::ofstream outFile(outputFilename);
//     std::cout << "output path: " << outputFilename << std::endl;

//     if (!outFile)
//     {
//         std::cerr << "Error opening file for writing history";
//         return;
//     }

//     // Write the header
//     outFile << "Date,Open,High,Low,Close,Volume\n";

//     // Set the limit for how many lines you want to write
//     int limit = 2600;
//     int linesWritten = 0;

//     std::string line;
//     bool isFirstLine = true; // Flag to identify the first line

//     while (linesWritten < limit && std::getline(inputFile, line))
//     {
//         // Check if it's the first line and if it's the header line
//         if (isFirstLine && line == "Date,Open,High,Low,Close,Volume")
//         {
//             isFirstLine = false; // Skip the first line
//             continue;
//         }

//         outFile << line << "\n";
//         linesWritten++;
//     }

//     // Write the data from histories
//     // Write the data from histories
//     for (const auto &history : histories)
//     {

//         if (linesWritten >= limit || history.date > currentDate)
//         {
//             break; // Stop writing if the limit or current date is reached
//         }

//         // Split the date strings into parts
//         std::vector<std::string> historyParts = Calendar::split(history.date, '-');
//         std::vector<std::string> currentParts = Calendar::split(currentDate, '/');

//         std::cout << "history date: " << history.date << std::endl;
//         std::cout << "current date: " << currentDate << std::endl;

//         int historyDay = std::stoi(historyParts[2]);
//         int historyMonth = std::stoi(historyParts[1]);
//         int historyYear = std::stoi(historyParts[0]);

//         int currentDay = std::stoi(currentParts[0]);
//         int currentMonth = std::stoi(currentParts[1]);
//         int currentYear = std::stoi(currentParts[2]);

//         // Compare years first
//         if (historyYear < currentYear)
//         {
//             // History date is in the past
//             outFile << history.date << ",";
//             outFile << "0,"; // Open
//             outFile << "0,"; // High
//             outFile << "0,"; // Low
//             outFile << history.closePrice << ",";
//             outFile << "0\n"; // Volume

//             linesWritten++;
//         }
//         else if (historyYear == currentYear)
//         {
//             // Same year, compare months
//             if (historyMonth < currentMonth || (historyMonth == currentMonth && historyDay <= currentDay))
//             {
//                 // History date is in the past or today
//                 outFile << history.date << ",";
//                 outFile << "0,"; // Open
//                 outFile << "0,"; // High
//                 outFile << "0,"; // Low
//                 outFile << history.closePrice << ",";
//                 outFile << "0\n"; // Volume

//                 linesWritten++;
//             }
//         }
//     }

//     std::cout << "marker - lines written: " << linesWritten << std::endl;

//     // Close both files
//     inputFile.close();
//     outFile.close();
// }
