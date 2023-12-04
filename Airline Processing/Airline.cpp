#include "Airline.h"

// Airline object constructor
Airline::Airline(std::string name)
{
    this->name = name;
}

// Return airline name
std::string Airline::getName()
{
    return name;
}

// Update ratings in each category for airline
void Airline::updateAirline(std::vector<std::string> stats)
{
    for (int i = 1; i < 9; i++)
    {
        // -1 is used as a flag for column without data
        // If -1 is encountered, move on
        if (std::stof(stats[i]) == -1)
            continue;
        scores[i-1] += std::stof(stats[i]);
        numReviews[i-1] += 1;
    }
}

// Return vector of airline ratings in each category
std::vector<float> Airline::getScores()
{
    return scores;
}

// Take average of each rating for the airline
void Airline::finalizeScores()
{
    for (int i = 0; i < 8; i++)
        scores[i] /= numReviews[i];
}
