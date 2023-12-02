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
    rapidcsv::Document file("./cmake-build-debug/reviews.csv", rapidcsv::LabelParams(-1, -1));
    int filePos = 0;
    while (filePos < file.GetRowCount())
    {
        std::vector<string> review = file.GetRow<string>(filePos);
        addReview(review);
        filePos++;
    }
}

void Processor::addReview(vector<std::string>& review)
{
    for (auto elem : airlines)
    {
        if (elem->name == review[0])
    }
    else
        Airline* airline = findAirline(review[8], review[9]);
    //airline->updateAirline(review);
}

Airline* Processor::findAirline(std::string source, std::string dest)
{
    Airline* res = nullptr;
    for (Airline* elem : sourceMap.at(source).at(dest))
    {

    }
}