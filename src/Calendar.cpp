#include "Calendar.h"
#include <iostream>
#include <chrono>

Calendar::Calendar() : year(2020), month(1), day(1), dayDuration(1.0) {} // 86400 seconds in a day

// void Calendar::update()
// {
//     auto currentTime = std::chrono::high_resolution_clock::now();
//     std::chrono::duration<double> elapsedTime = currentTime - lastUpdateTime;
//     lastUpdateTime = currentTime;

//     timePassed += elapsedTime.count() * timeMultiplier;

//     int daysPassed = static_cast<int>(timePassed / dayDuration);
//     day += daysPassed;
//     timePassed -= daysPassed * dayDuration;

//     while (day > daysInMonth[month - 1])
//     {
//         day -= daysInMonth[month - 1];
//         month++;
//         if (month > 12)
//         {
//             year++;
//             month = 1;
//         }
//     }
// }

bool Calendar::isLeapYear(int year) const
{
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

void Calendar::update()
{
    auto currentTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsedTime = currentTime - lastUpdateTime;
    lastUpdateTime = currentTime;

    timePassed += elapsedTime.count() * timeMultiplier;

    int daysPassed = static_cast<int>(timePassed / dayDuration);
    day += daysPassed;
    timePassed -= daysPassed * dayDuration;

    while (day > daysInMonth[month - 1])
    {
        if (month == 2 && isLeapYear(year))
        {
            day -= daysInMonth[month - 1] + 1;
        }
        else
        {
            day -= daysInMonth[month - 1];
        }

        month++;
        if (month > 12)
        {
            year++;
            month = 1;
        }
    }
}

int Calendar::getYear() const { return year; }
int Calendar::getMonth() const { return month; }
int Calendar::getDay() const { return day; }

/* WORKING BUT IS NOT ACCURATE USING DELTA TIME **/

// #include "Calendar.h"
// #include <iostream>
// #include <chrono>
// #include <thread>

// Calendar::Calendar() : year(2020), month(1), day(1), dayDuration(5.0) {}

// void Calendar::update(double deltaTime)
// {
//     timePassed += deltaTime;

//     int daysPassed = static_cast<int>(timePassed / dayDuration);
//     day += daysPassed;

//     if (day > 30)
//     {
//         month += day / 30;
//         day %= 30;
//     }
//     if (month > 12)
//     {
//         year += month / 12;
//         month %= 12;
//     }

//     timePassed -= daysPassed * dayDuration; // Remove full days from timePassed
// }

// int Calendar::getYear() const { return year; }
// int Calendar::getMonth() const { return month; }
// int Calendar::getDay() const { return day; }
