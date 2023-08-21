#include "Calendar.h"
#include <iostream>
#include <chrono>
#include <string>

/*!
    @file Calendar.cpp
    @brief Class which Creates an in-game timer based on elapsed real time.
    @author Ben Knox
*/

Calendar::Calendar() : year(2020), month(1), day(1), dayDuration(1.0) {} // dayduration = 1 day in game takes 1 second

/*!
    @brief Method to check whether a year is a leap year.
    @param year [in] the year to be checked
    @return true if the year is a leap year, and false if the year is not.
*/
bool Calendar::isLeapYear(int year) const
{
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

/*!
    @brief Method which increments the number days everytime it is called based on the time passed.
    @details This method will also update the current month and year as well since they are dependent upon the day.
        This method will also check if the clock has been paused at all and will subtract off all time spent in the paused state.
*/
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

/*!
    @brief Method starts the in-game calendar
    @details As well as starting the calendar, if the calendar is being started from a previously paused state, the time
        spent in the paused state will be subtracted from elapsed time.
*/
void Calendar::startCounting()
{
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

/*!
    @brief Method pauses the in-game calendar
    @details As well as pausing, will keep track of the real time which the clock was paused at so that any
        time spent in the paused state is not used when the calendar is updated.
*/
void Calendar::pauseCounting()
{
    if (countingStarted && !countingPaused)
    {
        countingPaused = true;
        pauseStartTime = std::chrono::high_resolution_clock::now();
    }
}

/*!
    @brief Method resets the in-game calendar
    @details Resets the calendar to a pre-determined date.
*/
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

/*!
    @brief Method to fast forward the calendar by any number of weeks, months, or years.
    @details This method will get the total number of days being skipped based off of the parameters,
        then will increment month and year while subtracting from total days until the new date is found.
    @param weeks [in] number of weeks to skip.
    @param months [in] number of months to skip.
    @param years [in] number of years to skip.
*/
void Calendar::skipTime(int weeks, int months, int years)
{
    if (weeks == 0 && months == 0 && years == 0)
        return; // No skipping needed

    // Calculate the total number of days to skip
    int totalDays = weeks * 7 + months * 30 + years * 365;

    // Calculate the new date
    day += totalDays;

    // Adjust month and year based on the new day
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

/*!
    @brief Getter method to find out if the calendar is currently counting or not.
    @return true if the calendar is counting, false if not.
*/
bool Calendar::isCounting() const
{
    return countingStarted && !countingPaused;
}

/*!
    @brief Getter method which gets the current in-game year.
    @return year as an int
*/
int Calendar::getYear() const { return year; }

/*!
    @brief Getter method which gets the current in-game month.
    @return month as an int
*/
int Calendar::getMonth() const { return month; }

/*!
    @brief Getter method which gets the current in-game day of the month.
    @return day as an int
*/
int Calendar::getDay() const { return day; }

/*!
    @brief Getter method which gets the current in-game date.
    @return date as a string
*/
std::string Calendar::getDate() const
{
    std::string strDay = std::to_string(day);
    std::string strMonth = std::to_string(month);
    std::string strYear = std::to_string(year);
    std::string date = strDay + "/" + strMonth + "/" + strYear;
    return date;
}