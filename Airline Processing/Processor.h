#pragma once
#include <unordered_set>
#include <unordered_map>
#include "SplayTree.cpp"
using namespace std;

class Processor
{
    SplayTree sourceTree; // Splay Tree that stores all source cities -- one of two main data structures
    unordered_map<string, unordered_map<string, vector<Airline*>>> sourceMap; // HashMap storing all source cities -- other main data structure
    unordered_set<Airline*> airlines; // Set containing all airlines available
    vector<Airline*> currRoute; // Vector containing airlines that run the route input by the user

public:
    Processor() = default;
    ~Processor() = default;

    void start(); // Generates Splay Tree and HashMap of sources
    void addReview(vector<string>&); // Adds reviews to backing data structures
    std::pair<double, double> setRouteVec(string source, string dest); // Sets currRoute to user input
    void sortRoute(int flag = 0); // Sorts currRoute based on user-selected category
    vector<Airline*> getRouteVec(); // Returns currRoute
};
