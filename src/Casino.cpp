#include "Casino.h"
#include <ctime>
#include <cstdlib>
#include <string>
#include <tuple>
#include <vector>

Casino::Casino() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
}
std::tuple<int, std::string> Casino::rouletteWheel() {
    int number = std::rand() % 37;
    std::string color;

    if (number == 0) {
        color = "G";
    } else if (number == 32 || number == 19 || number == 21 || number == 25 || number == 34 || number == 27 || number == 36 ||
               number == 30 || number == 23 || number == 5  || number == 16 || number == 1  || number == 14 || number == 9 ||
               number == 18 || number == 7  || number == 12 || number == 35 || number == 3) {
        color = "R";
    } else {
        color = "B";
    }

    return std::make_tuple(number, color);
}

double Casino::rouletteMultiplier(int guess) {
    int number;
    std::string color;
    std::tie(number, color) = rouletteWheel();
    
    if (guess == number) {
        return 35.0;
    }
    return 0.0;
}

double Casino::rouletteMultiplier(const std::string& guess) {
    int number;
    std::string color;
    std::tie(number, color) = rouletteWheel();

    if (guess == color) {
        if (color == "R" || color == "B") {
            return 2.0;
        } else if (color == "G") {
            return 17.0;
        }
    }
    return 0.0;
}

std::vector<std::string> Casino::slotMachineSpin() {
    std::vector<std::string> symbols = {"BAR", "7", "Cherry", "Lemon", "BAR", "7", "Cherry", "Lemon", "BAR", "Cherry", "Lemon", "Cherry", "Lemon", "Diamond"};
    std::vector<std::string> result(3);

    for (int i = 0; i < 3; ++i) {
        result[i] = symbols[std::rand() % symbols.size()];
    }
    return result;
}

double Casino::slotMachineMultiplier(const std::vector<std::string>& result) {
    if (result[0] == "Diamond" && result[1] == "Diamond" && result[2] == "Diamond") return 2000.0;
    if (result[0] == "7" && result[1] == "7" && result[2] == "7") return 300.0;
    if (result[0] == "BAR" && result[1] == "BAR" && result[2] == "BAR") return 100.0;
    if (result[0] == "Cherry" && result[1] == "Cherry" && result[2] == "Cherry") return 50.0;
    if (result[0] == "Lemon" && result[1] == "Lemon" && result[2] == "Lemon") return 25.0;
    return 0.0;
}

