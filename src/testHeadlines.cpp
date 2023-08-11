#include <iostream>
#include "Headline.h"

int main() {
    std::vector<Headline> headlines = Headline::read_from_csv("/data/headlines.csv");

    for (const auto& h : headlines) {
        if (h.type == "Tech") {
            std::cout << h.headline << " | " << h.multiplier << " | " << h.sector << " | " << h.type << std::endl;
        }
    }

    return 0;
}
