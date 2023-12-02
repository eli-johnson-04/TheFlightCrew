#include <iostream>
#include "SplayTree.cpp"
#include "Processor.h"
#include <fstream>
#include <sstream>
#include "rapidcsv.h"
#include <string>
#include <vector>
#include <unordered_map>
#include <map>

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

    sourceMap.emplace(review[9], unordered_map<string, vector<Airline*>>());

}
