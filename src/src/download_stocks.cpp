#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <curl/curl.h>
#include "stock.h"

// JSON parsing
#include <json/json.h>

// Used to store the data we get back from the server
std::string response_string;

// This function will be called by libcurl for each chunk of data received from the server
size_t writeFunction(void* ptr, size_t size, size_t nmemb, std::string* data) {
    data->append((char*)ptr, size * nmemb);
    return size * nmemb;
}

std::string getStockData(const std::string& symbol) {
    const std::string api_key = "YOUR_ALPHA_VANTAGE_API_KEY"; // replace with your Alpha Vantage API Key
    std::string url = "https://www.alphavantage.co/query?function=TIME_SERIES_DAILY&symbol=" + symbol + "&apikey=OE5NOBB6W3V7JEER";

    CURL* curl;
    CURLcode res;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeFunction);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_string);

        res = curl_easy_perform(curl);

        if(res != CURLE_OK)
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;

        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();

    return response_string;
}

std::vector<Stock> parseCSV(const std::string& csvFile) {
    std::ifstream data(csvFile);
    std::string line;
    std::vector<Stock> stocks;

    // Skip header line
    std::getline(data, line);

    // Go through each line
    while (std::getline(data, line)) {
        std::stringstream lineStream(line);
        std::string cell;
        std::vector<std::string> cells;

        // Break the line into cells
        while (std::getline(lineStream, cell, ',')) {
            cells.push_back(cell);
        }

        // Create a new Stock object from the cells and add it to the vector
        stocks.push_back(Stock(cells[0], cells[1], cells[2], cells[3], cells[4], cells[5], cells[6]));
    }

    return stocks;
}

int main() {
    std::vector<Stock> stocks = parseCSV("NASDAQ.csv");
    std::string symbol;

    std::cout << "Enter the symbol of the stock you want data for: ";
    std::cin >> symbol;

    std::string response_data = getStockData(symbol);

    // Parse JSON and get the needed data
    Json::Value jsonData;
    std::string errors;
    Json::CharReaderBuilder builder;
    const std::unique_ptr<Json::CharReader> reader(builder.newCharReader());

    if (!reader->parse(response_data.c_str(), response_data.c_str() + response_data.size(), &jsonData, &errors))
        std::cerr << "Error parsing the string" << std::endl;
    else {
        // Use the parsed JSON
        std::cout << "Parsed JSON data:" << std::endl << jsonData << std::endl;
    }

    return 0;
}
