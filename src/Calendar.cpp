#include "Calendar.h"
#include <iostream>
#include <chrono>
#include <string>

Calendar::Calendar() : year(2020), month(1), day(1), dayDuration(1.0) {} // dayduration = 1 day in game takes 1 second

bool Calendar::isLeapYear(int year) const
{
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

void Calendar::update()
{
    if (!countingStarted || countingPaused)
    {
        return; // Do nothing if counting hasn't started or is paused
    }

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

void Calendar::startCounting()
{
    countingStarted = true;
    countingPaused = false;
}

void Calendar::pauseCounting()
{
    countingPaused = true;
}

void Calendar::reset()
{
    countingStarted = false;
    countingPaused = false;
    year = 2020;
    month = 1;
    day = 1;
    timePassed = 0.0;
}

bool Calendar::isCounting() const
{
    return countingStarted && !countingPaused;
}

int Calendar::getYear() const { return year; }
int Calendar::getMonth() const { return month; }
int Calendar::getDay() const { return day; }
std::string Calendar::getDate() const
{
    std::string strDay = std::to_string(day);
    std::string strMonth = std::to_string(month);
    std::string strYear = std::to_string(year);
    std::string date = strDay + "/" + strMonth + "/" + strYear;
    return date;
}
