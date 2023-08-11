#ifndef NEWSGENERATOR_H
#define NEWSGENERATOR_H

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <ctime>
#include <cstdlib>
#include <algorithm>

// ChatGPTed

struct NewsItem {
    std::string headline;
    double multiplier;
};

class newsGenerator {
private:
    std::map<std::string, std::vector<NewsItem>> data;
    std::vector<NewsItem> worldEvents;
    std::string folders[4] = {"/data/news/financial/", "/data/news/tech/", "/data/news/funny/", "/data/news/rare/"};

    void loadCSV(const std::string& folder, const std::string& sector);

public:
    newsGenerator(unsigned int seed = static_cast<unsigned int>(time(0)));

    std::pair<std::string, double> getFinancialNews(const std::string& sector, unsigned int seed);

    void generateWorldEvents(unsigned int seed);

    std::vector<NewsItem> getWorldEvents() const;
};

#endif // NEWSGENERATOR_H
