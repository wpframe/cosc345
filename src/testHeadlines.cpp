#include <iostream>
#include "Headline.h"
#include "Stock.h"

int main() {
    std::vector<Headline> headlines = Headline::read_from_csv("data/headlines.csv");
    Stock x = Stock("AAPL", "Apple Inc.", 1000000000, 1980, "Technology", "Consumer Electronics");
    int seed = 112513251;
    for(int i = 0; i < 52; i++){
        std::cout << Headline::generateHeadline(x, seed++).first + "\n";
    }

    return 0;
}
