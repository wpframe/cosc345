#ifndef CASINO_H
#define CASINO_H

#include <string>
#include <tuple>
#include <vector>

class Casino {
public:
    Casino();

    std::tuple<int, std::string> rouletteWheel();
    double rouletteMultiplier(int guess);
    double rouletteMultiplier(const std::string& guess);

    std::vector<std::string> slotMachineSpin();
    double slotMachineMultiplier(const std::vector<std::string>& result);

private:
    std::tuple<std::string, std::string> drawCard();
    int computeHandTotal(const std::vector<std::tuple<std::string, std::string>>& hand);

    std::vector<std::tuple<std::string, std::string>> playerHand;
    std::vector<std::tuple<std::string, std::string>> dealerHand;
};

#endif
