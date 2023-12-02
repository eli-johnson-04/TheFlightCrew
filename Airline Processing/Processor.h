#pragma once
#include <string>
#include <fstream>
using namespace std;

class Processor
{
    vector<Airline*> sortResults();
public:
    void start(); // Generates Splay Tree and HashMap of sources
    vector<Airline*> getData(); // Returns sorted vector of airlines that fly a route
};
