#pragma once
#include <unordered_set>
#include <unordered_map>
#include "SplayTree.cpp"
using namespace std;

class Processor
{
    SplayTree sourceTree;
    unordered_map<string, unordered_map<string, vector<Airline*>>> sourceMap;
    unordered_set<Airline*> airlines;
    vector<Airline*> currRoute;

public:
    void start(); // Generates Splay Tree and HashMap of sources
    void addReview(vector<string>&);
    std::pair<double, double> getRouteVec(string source, string dest); // Returns sorted (according to flag) vector of airlines that fly a route
    void sortRoute(int flag = 0);
};
