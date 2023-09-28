#ifndef CASINO_TESTER_H
#define CASINO_TESTER_H

#include "Casino.h"

class CasinoTester {
public:
    CasinoTester();

    void runAllTests();
    void testRoulette();
    void testSlotMachine();

private:
    Casino casino;
};

#endif // CASINO_TESTER_H
