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
    std::vector<float> scores = std::vector<float>(8, 0); // Stores ratings for each category
    std::vector<int> numReviews = std::vector<int>(8, 0); // Stores number of reviews for each category
public:
    Airline(std::string name);
    ~Airline() = default;

    std::string getName(); // Returns airline name
    std::vector<float> getScores(); // Returns scores vector
    void updateAirline(std::vector<std::string> stats); // Updates airline ratings
    void finalizeScores(); // Takes average for each rating category
};