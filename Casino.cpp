#include "Casino.h"
#include <ctime>
#include <cstdlib>

Casino::Casino() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
}

int Casino::rouletteWheel() {
    return std::rand() % 37;
}

double Casino::rouletteMultiplier(int result) {
    if (result == 0) return 35.0;
    return 1.0;
}

std::vector<std::string> Casino::slotMachineSpin() {
    std::vector<std::string> symbols = {"BAR", "7", "Cherry", "Lemon"};
    std::vector<std::string> result(3);

    for (int i = 0; i < 3; ++i) {
        result[i] = symbols[std::rand() % symbols.size()];
    }
    return result;
}

double Casino::slotMachineMultiplier(const std::vector<std::string>& result) {
    if (result[0] == "7" && result[1] == "7" && result[2] == "7") return 10.0;
    if (result[0] == "BAR" && result[1] == "BAR" && result[2] == "BAR") return 5.0;
    if (result[0] == "Cherry" && result[1] == "Cherry" && result[2] == "Cherry") return 3.0;
    if (result[0] == "Lemon" && result[1] == "Lemon" && result[2] == "Lemon") return 2.0;
    return 0.0;
}

