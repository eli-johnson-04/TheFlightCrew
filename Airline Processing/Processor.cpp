#include <iostream>
#include <vector>
#include <algorithm>
#include "Processor.h"
#include "rapidcsv.h"

void Processor::start()
{
    // RapidCSV Library obtained from https://github.com/d99kris/rapidcsv

    // Create Document object without any headers from the source CSV
    rapidcsv::Document file("./cmake-build-debug/reviews.csv", rapidcsv::LabelParams(-1, -1));

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

    // If sourceMap doesn't contain the source city,
    // create new entry with corresponding destination map
    if (!sourceMap.count(source))
        sourceMap.emplace(source, unordered_map<string, vector<Airline*>>());

    // If destinationMap for source city doesn't contain destination city,
    // create new entry with corresponding airline vector
    auto destMap = sourceMap.at(source);
    if (!destMap.count(dest))
        destMap.emplace(dest, vector<Airline*>());

    // If airlineVec for destination city doesn't contain the airline being reviewed,
    // add it to the vector
    auto airlineVec = destMap.at(dest);
    if (find(airlineVec.begin(), airlineVec.end(), airline) == airlineVec.end())
        airlineVec.push_back(airline);

    // Part B - Splay Tree

    // If tree lacks city, add it
    if (!sourceTree.searchTree(source))
        sourceTree.insert(source);

    // If source city lacks destination city, add it
    destMap = sourceTree.searchTree(source)->destinations;
    if (!destMap.count(dest))
        destMap.emplace(dest, vector<Airline*>());

    // If destination city lacks airline, add it
    airlineVec = destMap.at(dest);
    if (find(airlineVec.begin(), airlineVec.end(), airline) == airlineVec.end())
        airlineVec.push_back(airline);
}
