#include "Calendar.h"
#include <iostream>
#include <chrono>
#include <string>
#include <sstream>

/*!
    @file
    @brief Class which Creates an in-game timer based on elapsed real time.
    @author Ben Knox
*/

Calendar::Calendar() : year(2023), month(1), day(1), dayDuration(1.0) {} // dayduration = 1 day in game takes 1 second

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
    @brief Method resets the in-game calendar
    @details Resets the calendar to a pre-determined date.
*/
void Calendar::reset()
{
    // Reset the calendar to the initial date
    countingStarted = false;
    countingPaused = false;
    year = 2023;
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

/*!
    @brief Method to get the current week count from the starting date of 01/01/2023
    @return totalWeeks
*/
int Calendar::getWeeks() const
{
    int totalDays = day + daysInMonth[month - 1] * (month - 1);

    for (int currYear = 2023; currYear < year; ++currYear)
    {
        if (isLeapYear(currYear))
        {
            totalDays += 366;
        }
        else
        {
            totalDays += 365;
        }
    }

    if (month > 2 && isLeapYear(year))
    {
        totalDays++;
    }

    int totalWeeks = totalDays / 7;
    return totalWeeks;
}

/*!
    @brief Method calculate when a users' study will end
    @details Study takes around 3 years depending on start date.
    @param date [in] date study started
    @return date which study will end
*/
std::string Calendar::calculateStudyEnd(const std::string &date)
{
    std::istringstream iss1(date);
    char delimiter1;
    int days, months, years;
    if (!(iss1 >> days >> delimiter1 >> months >> delimiter1 >> years) || delimiter1 != '/')
    {
        return "Invalid date format";
    }

    years += 3;

    months = 11;

    std::string result = std::to_string(days) + "/" + std::to_string(months) + "/" + std::to_string(years);
    return result;
}

/*!
    @brief Method which calculates the time difference between two dates.
    @details returns 0, 0 if the first date is after the second date.
    @param date1 [in] the first date being compared
    @param date2 [in] the second date being compared
    @return a tuple of months and years of the date difference
*/
DateDifference Calendar::calcDateDifference(const std::string &date1, const std::string &date2)
{
    DateDifference result = {0, 0};

    std::istringstream iss1(date1);
    char delimiter1;
    int day1, month1, year1;
    if (!(iss1 >> day1 >> delimiter1 >> month1 >> delimiter1 >> year1) || delimiter1 != '/')
    {
        result.years = -1;
        result.months = -1;
    }

    std::istringstream iss2(date2);
    char delimiter2;
    int day2, month2, year2;
    if (!(iss2 >> day2 >> delimiter2 >> month2 >> delimiter2 >> year2) || delimiter2 != '/')
    {
        result.years = -1;
        result.months = -1;
    }

    // Calculate the difference in years and months
    result.years = year2 - year1;
    result.months = month2 - month1;

    if (result.months < 0)
    {
        result.years--;
        result.months += 12;
    }

    if (result.years < 0)
    {
        result.months = 0;
        result.years = 0;
    }

    return result;
}

/*!
    @brief Method sets the date
    @param date [in] the date to be set
*/
void Calendar::setDate(const std::string &date)
{
    std::istringstream iss(date);
    char delimiter;
    int newDay, newMonth, newYear;

    if (!(iss >> newDay >> delimiter >> newMonth >> delimiter >> newYear) || delimiter != '/')
    {
        std::cerr << "Invalid date format: " << date << std::endl;
        return;
    }

    if (newYear < 2023)
    {
        // Handle setting a date before the starting year (2023)
        std::cerr << "Cannot set a date before 2023." << std::endl;
        return;
    }

    // Check if the new month is within a valid range (1-12)
    if (newMonth < 1 || newMonth > 12)
    {
        std::cerr << "Invalid month: " << newMonth << std::endl;
        return;
    }

    // Check if the new day is within a valid range for the given month
    if (newDay < 1 || newDay > daysInMonth[newMonth - 1])
    {
        std::cerr << "Invalid day: " << newDay << std::endl;
        return;
    }

    year = newYear;
    month = newMonth;
    day = newDay;
}
