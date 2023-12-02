#pragma once
#include <string>
#include <vector>

class Airline
{
    std::string name;
    int numReviews;
    std::vector<float> ratings = std::vector<float>(8, 0);
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
public:
    Airline(std::string name);
    ~Airline() = default;
    void updateAirline(std::vector<std::string> stats); // Updates airline stats based on input
};