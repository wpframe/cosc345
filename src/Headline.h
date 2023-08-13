#ifndef HEADLINE_H
#define HEADLINE_H

#include <string>
#include <vector>
#include "Stock.h"

class Headline {
public:
    std::string headline;
    double multiplier;
    std::string sector;
    std::string type;

    static std::vector<Headline> financial_news;
    static std::vector<Headline> tech_news;
    static std::vector<Headline> funny_news;
    static std::vector<Headline> rare_news;
    static std::vector<Headline> world_news;

    Headline(const std::string& h, const double& m, const std::string& s, const std::string& t);
    static std::pair<std::string, double> generateHeadline(const Stock& stock, unsigned int seed);
    static std::vector<Headline> read_from_csv(const std::string& filename);
};

#endif // HEADLINE_H
