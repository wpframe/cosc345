/*!
    @file
    @brief The implementation for the Headline class.
    @details It has functions to read in a CSV file of news headlines,
                and generate a news headline for a specific stock.
*/

#include "Headline.h"
#include "Stock.h"
#include "PathUtil.h"
#include <iostream>
#include <fstream>
#include <sstream>

// Vectors of the different types of news.
std::vector<Headline> Headline::financial_news;
std::vector<Headline> Headline::tech_news;
std::vector<Headline> Headline::funny_news;
std::vector<Headline> Headline::rare_news;
std::vector<Headline> Headline::world_news;

/*!
    @brief The constructor for the Headline class.
    @details Takes and initializes the headline, multiplier, sector, and type.
    @param h The headline.
    @param m The multiplier.
    @param s The sector.
    @param t The type.
*/
Headline::Headline(const std::string &h, const double &m, const std::string &s, const std::string &t)
    : headline(h), multiplier(m), sector(s), type(t) {}

/*!
    @brief Reads in a CSV file of news headlines.
    @details It adds all of the headlines in the file to different static vectors depending on type.
    @param filename The name of the file to parse.
*/
void Headline::readFromCSV(const std::string &filename)
{
    std::vector<Headline> headlines;
    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "Failed to open the CSV file." << std::endl;
        return;
    }

    std::string line;
    // Skip the header line
    std::getline(file, line);

    while (std::getline(file, line))
    {
        std::istringstream ss(line);
        std::string headline, multiplier, sector, type, token;

        // Read headline (considering it might contain commas)
        std::getline(ss, headline, '"');
        std::getline(ss, headline, '"');
        std::getline(ss, token, ','); // skip the comma after the headline

        std::getline(ss, multiplier, ',');
        std::getline(ss, sector, ',');
        std::getline(ss, type, ',');

        headlines.emplace_back(headline, std::stod(multiplier), sector, type);
    }

    file.close();

    for (const auto &h : headlines)
    {
        if (h.type == "Financial")
        {
            financial_news.push_back(h);
        }
        else if (h.type == "Tech")
        {
            tech_news.push_back(h);
        }
        else if (h.type == "Funny")
        {
            funny_news.push_back(h);
        }
        else if (h.type == "Rare")
        {
            rare_news.push_back(h);
        }
        else if (h.type == "World")
        {
            world_news.push_back(h);
        }
    }
}

/*!
    @brief Generates a news headline for a specific stock.
    @details It randomly selects a headline from one of the vectors.
    @param stock The stock to generate a headline for.
    @param seed The seed for the random number generator.
    @return A pair containing the headline and the multiplier.
*/
std::pair<std::string, double> Headline::generateHeadline(const Stock &stock, unsigned int seed)
{
    seed *= rand();
    seed /= rand();
    seed += rand();
    srand(seed); // Seed the random number generator with the provided seed

    int financial_chance = rand() % 2;
    int rare_chance = rand() % 30;
    int funny_chance = rand() % 8;
    // int financial_chance = 20;
    // int rare_chance = rand() % 300;
    // int funny_chance = rand() % 80;
    int tech_chance = (stock.sector == "Technology") ? rand() % 600 : 601; // If not tech, set it to an impossible value

    std::vector<Headline> *selected_news = nullptr;

    if (financial_chance == 0)
    {
        selected_news = &financial_news;
        // std::cout << "lenght of financial news: " << financial_news.size() << std::endl;
    }
    else if (rare_chance == 0)
    {
        selected_news = &rare_news;
    }
    else if (funny_chance == 0)
    {
        selected_news = &funny_news;
    }
    else if (tech_chance == 0)
    {
        selected_news = &tech_news;
    }

    if (selected_news && !selected_news->empty())
    {
        int chosen_index = rand() % selected_news->size();
        std::string selected_headline = (*selected_news)[chosen_index].headline;
        double selected_multiplier = (*selected_news)[chosen_index].multiplier;

        // Replace the placeholder with the stock's name
        size_t pos = selected_headline.find("[Stock]");
        if (pos != std::string::npos)
        {
            selected_headline.replace(pos, 7, stock.name);
        }

        return {selected_headline, selected_multiplier}; // Return both the headline and the multiplier
    }
    else
    {
        return {"", 1}; // Return empty strings if no headline is selected
    }
}