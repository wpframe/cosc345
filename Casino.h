#ifndef CASINO_H
#define CASINO_H

#include <string>
#include <tuple>
#include <vector>

class Casino {
public:
    Casino();

    int rouletteWheel();
    double rouletteMultiplier(int result);

    std::vector<std::string> slotMachineSpin();
    double slotMachineMultiplier(const std::vector<std::string>& result);

#endif
