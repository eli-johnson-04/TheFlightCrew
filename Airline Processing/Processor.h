#pragma once
#include <unordered_set>
#include "SplayTree.cpp"
using namespace std;

class Processor
{
    SplayTree sourceTree;
    unordered_map<string, unordered_map<string, vector<Airline*>>> sourceMap;
    unordered_set<Airline*> airlines;

    vector<Airline*> sortResults(); // sort pre print
public:
    void start(); // Generates Splay Tree and HashMap of sources
    void addReview(vector<string>&);
    vector<Airline*> getData(); // Returns sorted vector of airlines that fly a route
};
