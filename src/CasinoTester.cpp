#include "CasinoTester.h"
#include <iostream>

CasinoTester::CasinoTester() : casino() {}

void CasinoTester::runAllTests() {
    testRoulette();
    testSlotMachine();
}

// ChatGPT'd tests

void CasinoTester::testRoulette() {
    std::cout << "Testing Roulette...\n";

    // Testing specific number bet
    std::tuple<int, std::string> result = casino.rouletteWheel();
    int numberResult = std::get<0>(result);
    std::string colorResult = std::get<1>(result);
    double numberMultiplier = casino.rouletteMultiplier(23);
    std::cout << "Roulette Number Result: " << numberResult << ", Bet on 23, Multiplier: " << numberMultiplier << "\n";

    // Testing color bets
    double redMultiplier = casino.rouletteMultiplier("R");
    std::cout << "Roulette Color Result: " << colorResult << ", Bet on Red, Multiplier: " << redMultiplier << "\n";

    double blackMultiplier = casino.rouletteMultiplier("B");
    std::cout << "Roulette Color Result: " << colorResult << ", Bet on Black, Multiplier: " << blackMultiplier << "\n";

    double greenMultiplier = casino.rouletteMultiplier("G");
    std::cout << "Roulette Color Result: " << colorResult << ", Bet on Green, Multiplier: " << greenMultiplier << "\n\n";
}

void CasinoTester::testSlotMachine() {
    std::cout << "Testing Slot Machine...\n";
    auto result = casino.slotMachineSpin();
    double multiplier = casino.slotMachineMultiplier(result);
    std::cout << "Slot Machine Result: " << result[0] << ", " << result[1] << ", " << result[2]
              << ", Multiplier: " << multiplier << "\n\n";
}


