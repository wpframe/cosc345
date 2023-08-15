#ifndef CALENDAR_H
#define CALENDAR_H

#include <chrono>

class Calendar
{
public:
    Calendar(); // Constructor

    void update();
    int getYear() const;
    int getMonth() const;
    int getDay() const;
    bool isLeapYear(int year) const;

private:
    double dayDuration; // Duration of a day in seconds
    double timePassed = 0.0;
    int day = 1;
    int month = 1;
    int year = 2020;
    double timeMultiplier = 1.0;
    const int daysInMonth[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    std::chrono::time_point<std::chrono::high_resolution_clock> lastUpdateTime =
        std::chrono::high_resolution_clock::now();
};

#endif // CALENDAR_H

/* WORKING BUT IS NOT ACCURATE USING DELTA TIME **/

// #ifndef CALENDAR_H
// #define CALENDAR_H
// #include <iostream>

// class Calendar
// {
// public:
//     Calendar();

//     void update(double deltaTime);

//     int getYear() const;
//     int getMonth() const;
//     int getDay() const;

// private:
//     int year;
//     int month;
//     int day;
//     double dayDuration;
//     double timePassed = 0.0;
// };

// #endif // GAME_CALENDAR_H
