#ifndef CALENDAR_H
#define CALENDAR_H

#include <string>
#include <chrono>
#include <vector>

struct DateDifference
{
    int years;
    int months;
};

class Calendar
{
public:
    Calendar();

    int getYear() const;
    int getMonth() const;
    int getDay() const;
    bool isLeapYear(int year) const;
    std::string getDate() const;
    int getWeeks() const;

    void reset();
    void skipTime(int weeks, int months, int years);
    bool isCounting() const;
    std::string calculateDateDifference(const std::string &date1, const std::string &date2);
    DateDifference calcDateDifference(const std::string &date1, const std::string &date2);
    std::string calculateStudyEnd(const std::string &date);
    void setDate(const std::string &date);
    static std::vector<std::string> split(const std::string &s, char delimiter);

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
};

extern Calendar calendar;
#endif // CALENDAR_H
