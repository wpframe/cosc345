#ifndef CALENDAR_H
#define CALENDAR_H

#include <string>
#include <chrono>

class Calendar
{
public:
    Calendar();

    void update();
    int getYear() const;
    int getMonth() const;
    int getDay() const;
    bool isLeapYear(int year) const;
    std::string getDate() const;

    void startCounting();
    void pauseCounting();
    void reset();
    bool isCounting() const;

private:
    bool countingStarted = false;
    bool countingPaused = false;
    double dayDuration; // Duration of a day in seconds
    double timePassed = 0.0;
    int day = 1;
    int month = 1;
    int year = 2020;
    double timeMultiplier = 1.0;
    const int daysInMonth[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    std::chrono::time_point<std::chrono::high_resolution_clock> lastUpdateTime =
        std::chrono::high_resolution_clock::now();
    std::chrono::time_point<std::chrono::high_resolution_clock> pauseStartTime =
        std::chrono::high_resolution_clock::now();
};

#endif // CALENDAR_H
