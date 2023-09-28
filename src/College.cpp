/*!
    @file
    @brief The implementation for the Stock class.
    @details It holds the neccesary information for each stock, most importantly its symbol, name, and history.
*/

#include "Portfolio.h"
#include "College.h"
#include "PathUtil.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>

int totalEnrolment = 0;
int salary = 40000;
/*!
    @brief The constructor for the College class.
    @details Takes and initializes the name, rank, tuition, and enrolmentNumber.
    @param collegeName The college's name.
    @param rank The college's rank in America.
    @param tuition The Average tuition per year for the college in 2022.
    @param enrolmentNumber The number of people enrolled in 2022.
*/

College::College(const std::string &collegeName, int rank, int tuition, int enrolmentNumber)
    : collegeName(collegeName), rank(rank), tuition(tuition), enrolmentNumber(enrolmentNumber) {}

std::vector<College> parseCollegeCSV(const std::string &filename)
{
    std::vector<College> colleges;
    std::ifstream file(filename);

    if (!file.is_open())
    {
        std::cerr << "Failed to open the file: " << filename << std::endl;
        return colleges;
    }

    std::string line;
    // Skip the header line
    std::getline(file, line);

    while (std::getline(file, line))
    {
        std::stringstream ss(line);
        std::string token;

        std::string collegeName, rankStr, tuitionStr, enrolmentStr;

        std::getline(ss, collegeName, ',');
        std::getline(ss, rankStr, ',');
        std::getline(ss, tuitionStr, ',');
        std::getline(ss, enrolmentStr, ',');

        try
        {
            int rank = std::stoi(rankStr);
            int tuition = std::stoi(tuitionStr);
            int enrolmentNumbers = std::stoi(enrolmentStr);
            totalEnrolment += enrolmentNumbers;

            // Create a College object and add it to the vector.
            colleges.emplace_back(collegeName, rank, tuition, enrolmentNumbers);
        }
        catch (const std::exception &e)
        {
            // Handle conversion errors if needed.
            std::cerr << "Error converting data: " << e.what() << std::endl;
        }
    }

    file.close();
    return colleges;
}
std::string calculateResponse(College selectedCollege, Portfolio portfolio)
{
    // Seed the random number generator with the current time
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    // Define admission thresholds based on rank
    int admissionThreshold = 0;

    // Adjust admission thresholds based on the selectedCollege's rank
    // Lower-ranked colleges have a lower threshold for admission
    // Higher-ranked colleges have a higher threshold for admission
    if (selectedCollege.rank <= 20)
    {
        admissionThreshold = 500;
    }
    else if (selectedCollege.rank <= 50)
    {
        admissionThreshold = 2000;
    }
    else if (selectedCollege.rank <= 100)
    {
        admissionThreshold = 5000;
    }
    else
    {
        admissionThreshold = 7000;
    }

    // Generate a random number between 0 and 10000
    int randomValue = std::rand() % 10001;

    float totalProfit = portfolio.getTotalBalance();

    // Check if the randomValue and totalProfit meet the admission criteria
    if (randomValue < admissionThreshold + (totalProfit / 100))
    {
        // The player is successful in getting into the college
        return "success";
    }
    else
    {
        // The player is unsuccessful in getting into the college
        return "unsuccessful";
    }
}

College getCollege(std::string &collegeName, std::vector<College> colleges)
{
    for (const College &college : colleges)
    {
        if (collegeName == college.collegeName)
        {
            return college;
        }
    }
    return colleges[0];
}

float randomFloat(float min, float max)
{
    return min + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (max - min)));
}

int randomInt(int min, int max)
{
    return min + static_cast<int>(rand()) / (static_cast<int>(RAND_MAX / (max - min)));
}

void calculateSalary(int monthsSincePromotion)
{
    bool promotionDue = monthsSincePromotion >= randomInt(7, 15);

    float raisePercentage = 0.0;
    if (promotionDue)
    {
        raisePercentage = randomFloat(0.04f, 0.20f);
    }

    int newSalary = static_cast<int>(salary * (1 + raisePercentage));
    salary = newSalary;
}

int getSalary()
{
    return salary;
}
