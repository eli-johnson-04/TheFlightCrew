#include "Airline.h"

std::string Airline::getName()
{
    return name;
}

void Airline::updateAirline(std::vector<std::string> stats)
{
    numReviews++;
    for (int i = 1; i < 9; i++)
    {
        if (std::stof(stats[i]) == -1)
            continue;
        scores[i-1] += std::stof(stats[i]);
    }
}

std::vector<float> Airline::getScores()
{
    return scores;
}

void Airline::finalizeScores()
{
    for (auto& rating : scores)
        rating / numReviews;
}
