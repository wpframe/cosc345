#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <ctime>
#include <cstdlib>
#include <algorithm>

struct NewsItem {
    std::string headline;
    double multiplier;
};

class newsGenerator {
private:
    std::map<std::string, std::vector<NewsItem>> data;
    std::vector<NewsItem> worldEvents;
    std::string folders[4] = {"/data/news/financial/", "/data/news/tech/", "/data/news/funny/", "/data/news/rare/"};

    void loadCSV(const std::string& folder, const std::string& sector) {
        std::ifstream file(folder + sector + ".csv");
        std::string line, headline;
        double multiplier;

        while (std::getline(file, line)) {
            size_t pos = line.find(",");
            if (pos != std::string::npos) {
                headline = line.substr(0, pos);
                multiplier = std::stod(line.substr(pos + 1));
                data[sector].push_back({headline, multiplier});
            }
        }
    }

public:
    newsGenerator(unsigned int seed = static_cast<unsigned int>(time(0))) {
        srand(seed);

        for (const auto& folder : folders) {
            for (const auto& sector : {"Basic Materials", "Finance", "Real Estate", "Consumer Discretionary", 
                                       "Health Care", "Technology", "Consumer Staples", "Industrials", 
                                       "Telecommunications", "Energy", "Miscellaneous", "Utilities"}) {
                if (folder == "/tech/" && sector != "Technology") continue;
                loadCSV(folder, sector);
            }
        }
    }

    std::pair<std::string, double> getFinancialNews(const std::string& sector, unsigned int seed) {
        srand(seed);

        int techChance = rand() % 1500;
        int rareChance = rand() % 3000;
        int financialChance = rand() % 1000;
        int funnyChance = rand() % 1500;

        if (sector == "Technology" && techChance == 0) {
            NewsItem item = data["Technology"][rand() % data["Technology"].size()];
            return {item.headline, item.multiplier};
        }
        if (rareChance == 0) {
            NewsItem item = data["Miscellaneous"][rand() % data["Miscellaneous"].size()];
            return {item.headline, item.multiplier};
        }
        if (financialChance == 0) {
            if (data.find(sector) != data.end() && !data[sector].empty()) {
                NewsItem item = data[sector][rand() % data[sector].size()];
                return {item.headline, item.multiplier};
            } else {
                NewsItem item = data["Miscellaneous"][rand() % data["Miscellaneous"].size()];
                return {item.headline, item.multiplier};
            }
        }
        if (funnyChance == 0) {
            NewsItem item = data["Miscellaneous"][rand() % data["Miscellaneous"].size()];
            return {item.headline, item.multiplier};
        }

        if (data.find(sector) != data.end() && !data[sector].empty()) {
            NewsItem item = data[sector][rand() % data[sector].size()];
            return {item.headline, item.multiplier};
        } else {
            NewsItem item = data["Miscellaneous"][rand() % data["Miscellaneous"].size()];
            return {item.headline, item.multiplier};
        }
    }

    void generateWorldEvents(unsigned int seed) {
        srand(seed);
        worldEvents.clear();
        std::ifstream file("/data/news/world_news.csv");
        std::string line, headline;
        double multiplier;
        std::vector<NewsItem> allWorldNews;

        while (std::getline(file, line)) {
            size_t pos = line.find(",");
            if (pos != std::string::npos) {
                headline = line.substr(0, pos);
                multiplier = std::stod(line.substr(pos + 1));
                allWorldNews.push_back({headline, multiplier});
            }
        }

        std::random_shuffle(allWorldNews.begin(), allWorldNews.end());
        for (int i = 0; i < 10 && i < allWorldNews.size(); i++) {
            worldEvents.push_back(allWorldNews[i]);
        }
    }

    std::vector<NewsItem> getWorldEvents() const {
        return worldEvents;
    }
};

// int main() {
//     unsigned int seed = 12345; // Example seed
//     newsGenerator generator(seed);
//     auto news = generator.getFinancialNews("Technology", seed);
//     std::cout << news.first << " with multiplier: " << news.second << std::endl;

//     generator.generateWorldEvents(seed);
//     auto events = generator.getWorldEvents();
//     for (const auto& event : events) {
//         std::cout << event.headline << " with multiplier: " << event.multiplier << std::endl;
//     }
//     return 0;
// }
