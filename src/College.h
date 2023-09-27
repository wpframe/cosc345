#ifndef COLLEGE_H
#define COLLEGE_H

#include <string>
#include <vector>

class College
{
public:
    // Constructor
    College(const std::string &collegeName, int rank, int tuition, int enrolmentNumber);

    // private:
    std::string collegeName;
    int rank;
    int tuition;
    int enrolmentNumber;
    int totalEnrolment;
};

std::vector<College> parseCollegeCSV(const std::string &filename);
std::string calculateResponse(College selectedCollege, Portfolio portfolio);
College getCollege(std::string &collegeName, std::vector<College> colleges);

#endif
