#include "Airline.h"

Airline::Airline(std::string name)
{
    this->name = name;
}

std::string Airline::getName()
{
    return name;
}

void Airline::updateAirline(std::vector<std::string> stats)
{
    for (int i = 1; i < 9; i++)
    {
        if (std::stof(stats[i]) == -1)
            continue;
        scores[i-1] += std::stof(stats[i]);
        numReviews[i-1] += 1;
    }
}

std::vector<float> Airline::getScores()
{
    return scores;
}

void Airline::finalizeScores()
{
    for (int i = 0; i < 8; i++)
        scores[i] /= numReviews[i];
}
