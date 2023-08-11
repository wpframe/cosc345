#ifndef HEADLINE_H
#define HEADLINE_H

#include <string>
#include <vector>

class Headline {
public:
    std::string headline;
    std::string multiplier;
    std::string sector;
    std::string type;

    Headline(const std::string& h, const std::string& m, const std::string& s, const std::string& t);
    
    static std::vector<Headline> read_from_csv(const std::string& filename);
};

#endif // HEADLINE_H
