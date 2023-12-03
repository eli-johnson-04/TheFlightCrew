#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include "Processor.h"
#include "rapidcsv.h"

void Processor::start()
{
    // RapidCSV Library obtained from https://github.com/d99kris/rapidcsv

    // Create Document object without any headers from the source CSV
    rapidcsv::Document file("AirlineData.csv", rapidcsv::LabelParams(-1, -1));

    // Position counter to store current line number
    int filePos = 0;

    // Read entire file
    while (filePos < file.GetRowCount())
    {
        // Obtain vector containing all values in the row (Airline name, ratings, source city, destination city)
        std::vector<string> review = file.GetRow<string>(filePos);

        // Add review to source data structures
        addReview(review);
        filePos++;
    }

    for (auto airline : airlines)
        airline->finalizeScores();

}

void Processor::addReview(vector<std::string>& review)
{
    // Stage 1 - Airline Generation/Updating
    //--------------------------------------
    bool exists = false; // flag to determine if airline exists already
    Airline* airline = nullptr;

    // Check to see if airline already exists
    for (auto elem : airlines)
    {
        if (elem->getName() == review[0])
        {
            // Update airline stats if so
            elem->updateAirline(review);
            airline = elem;
            exists = true;
        }
    }

    // If airline doesn't exist, generate new Airline object
    if (!exists)
    {
        airline = new Airline(review[0]);
        airlines.emplace(airline);
        airline->updateAirline(review);
    }

    // Stage 2 - Data Structure Integration
    //-------------------------------------

    // Part A - HashMap

    // Store source and destination city names as vars
    string source = review[9];
    string dest = review[10];

    // Checks if review is associated with a route
    // Only add to map if a route is associated with the review
    if(source != "NO_SOURCE")
    {
        // If sourceMap doesn't contain the source city,
        // create new entry with corresponding destination map
        if (!sourceMap.count(source))
            sourceMap.emplace(source, unordered_map<string, vector<Airline*>>());

        // If destinationMap for source city doesn't contain destination city,
        // create new entry with corresponding airline vector
        auto& destMapMap = sourceMap.at(source);
        if (!destMapMap.count(dest))
            destMapMap.emplace(dest, vector<Airline*>());

        // If airlineVec for destination city doesn't contain the airline being reviewed,
        // add it to the vector
        auto& airlineVec = destMapMap.at(dest);
        if (find(airlineVec.begin(), airlineVec.end(), airline) == airlineVec.end())
            airlineVec.push_back(airline);

        // Part B - Splay Tree

        // If tree lacks city, add it
        if (!sourceTree.searchTree(source))
            sourceTree.insert(source);

        // If source city lacks destination city, add it
        auto& destMapTree = sourceTree.searchTree(source)->destinations;
        if (!destMapTree.count(dest))
            destMapTree.emplace(dest, vector<Airline*>());

        // If destination city lacks airline, add it
        airlineVec = destMapTree.at(dest);
        if (find(airlineVec.begin(), airlineVec.end(), airline) == airlineVec.end())
            airlineVec.push_back(airline);
    }
}

void Processor::sortRoute(int flag)
{
    // Lambda function to sort by specified category
    // Code adapted from https://stackoverflow.com/questions/1380463/sorting-a-vector-of-custom-objects
    std::sort(currRoute.begin(), currRoute.end(), [&](const auto& x, const auto& y)
    {return x->getScores()[flag] > y->getScores()[flag];});
}

std::pair<double, double> Processor::setRouteVec(string source, string dest)
{
    // Time variables for the HashMap and Splay Tree
    double mapTime, treeTime;


    // Part A - HashMap

    // Start timer
    auto start = std::chrono::high_resolution_clock::now();

    // Retrieve airline vector from HashMap
    vector<Airline*> vec = sourceMap.at(source).at(dest);

    // Stop timer and store total time to find and sort data
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = end - start;
    mapTime = diff.count();


    // Part B - Splay Tree

    // Start timer
    start = std::chrono::high_resolution_clock::now();

    // Retrieve airline vector from Splay Tree
    vec = sourceTree.searchTree(source)->destinations.at(dest);

    // Stop timer and store total time to find and sort data
    end = std::chrono::high_resolution_clock::now();
    diff = end - start;
    treeTime = diff.count();

    currRoute = vec;

    // Return pair with total time to execute for both data structures
    return std::make_pair(mapTime, treeTime);
}

vector<Airline*> Processor::getRouteVec()
{
    return currRoute;
}