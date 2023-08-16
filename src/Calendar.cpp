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
    if (!countingStarted)
    {
        return; // Do nothing if counting hasn't started
    }

    // Calculating elapsed time since timer started
    auto currentTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsedTime = currentTime - lastUpdateTime;

    lastUpdateTime = currentTime;

    // Only increment timePassed if counting is not paused
    if (!countingPaused)
    {
        timePassed += elapsedTime.count() * timeMultiplier;
    }

    // Calculating daysPassed based on how much time has passed since counting started
    int daysPassed = static_cast<int>(timePassed / dayDuration);
    day += daysPassed;
    timePassed -= daysPassed * dayDuration;

    // Calendar formatting
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
    // set boolean
    countingStarted = true;

    // if starting from a paused state, subtract the amount of time paused for
    if (countingPaused)
    {
        countingPaused = false;
        auto currentTime = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsedTime = currentTime - pauseStartTime;
        timePassed -= elapsedTime.count() * timeMultiplier;
    }
}

void Calendar::pauseCounting()
{
    if (countingStarted && !countingPaused)
    {
        countingPaused = true;
        // Set pauseStartTime for use when the time is started again,
        // so that the amount of time paused for can be subtracted
        pauseStartTime = std::chrono::high_resolution_clock::now();
    }
}

void Calendar::reset()
{
    // Reset the calendar to the initial date
    countingStarted = false;
    countingPaused = false;
    year = 2020;
    month = 1;
    day = 1;
    timePassed = 0.0;
}

bool Calendar::isCounting() const
{
    // Method which returns whether calendar is currently counting
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
