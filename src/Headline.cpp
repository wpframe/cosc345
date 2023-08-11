#include "Headline.h"
#include <iostream>
#include <fstream>
#include <sstream>

Headline::Headline(const std::string& h, const std::string& m, const std::string& s, const std::string& t)
    : headline(h), multiplier(m), sector(s), type(t) {}

std::vector<Headline> Headline::read_from_csv(const std::string& filename) {
    std::vector<Headline> headlines;
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open the CSV file." << std::endl;
        return headlines;
    }

    std::string line;
    // Skip the header line
    std::getline(file, line);

    while (std::getline(file, line)) {
        std::istringstream ss(line);
        std::string headline, multiplier, sector, type, token;

        // Read headline (considering it might contain commas)
        std::getline(ss, headline, '"');
        std::getline(ss, headline, '"');
        std::getline(ss, token, ',');  // skip the comma after the headline

        std::getline(ss, multiplier, ',');
        std::getline(ss, sector, ',');
        std::getline(ss, type, ',');

        headlines.emplace_back(headline, multiplier, sector, type);
    }

    file.close();
    return headlines;
}
