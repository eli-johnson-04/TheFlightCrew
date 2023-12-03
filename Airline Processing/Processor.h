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

public:
    void start(); // Generates Splay Tree and HashMap of sources
    void addReview(vector<string>&);
    tuple<vector<Airline*>, double, double> getData(string source, string dest, int flag = 0); // Returns sorted (according to flag) vector of airlines that fly a route
};
