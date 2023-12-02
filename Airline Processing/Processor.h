#pragma once
#include <unordered_set>
#include "SplayTree.cpp"
using namespace std;

class Processor
{
    struct Airline
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

    SplayTree sourceTree;
    unordered_map<string, unordered_map<string, vector<Airline*>>> sourceMap;
    unordered_set<Airline*> airlines;

    vector<Airline*> sortResults();
    Airline* findAirline(string source, string dest);
public:
    void start(); // Generates Splay Tree and HashMap of sources
    void addReview(vector<string>&);
    vector<Airline*> getData(); // Returns sorted vector of airlines that fly a route
};