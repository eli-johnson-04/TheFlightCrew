#pragma once
#include <string>
#include <vector>

class Airline
{
    std::string name;
    /*
     * Vector Indices Legend
     * 0 - Overall
     * 1 - Entertainment
     * 2 - Food
     * 3 - Comfort
     * 4 - Service
     * 5 - Value
     * 6 - Ground Service
     * 7 - Wifi
     */
    std::vector<float> scores = std::vector<float>(8, 0);
    std::vector<int> numReviews = std::vector<int>(8, 0);
public:
    Airline(std::string name);
    ~Airline() = default;
    std::string getName();
    std::vector<float> getScores();
    void updateAirline(std::vector<std::string> stats); // Updates airline stats based on input
    void finalizeScores();
};