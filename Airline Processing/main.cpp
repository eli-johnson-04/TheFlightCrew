#include <iostream>
#include <iomanip>
#include <string>
#include "Processor.h"

int main()
{
    // Initialize Processing object
    Processor* prog = new Processor();

    prog->start(); // Generate backing Splay Tree and HashMap

    // Sets route and calculates & displays access time for each structure
    std::pair<double, double> timePair = prog->setRouteVec("johannesburg", "paris");

    // Handles invalid searches
    if (timePair.first == -1)
        return -1;

    std::cout << "Time (Map): " << timePair.first << std::endl;
    std::cout << "Time (Tree): " << timePair.second << std::endl;

    // Retrieve airlines that run the route
    auto routeVec = prog->getRouteVec();

    // Set ratings precision to 1 decimal place
    std::cout << std::fixed << std::setprecision(1) << std::endl;

    // Display each airline and their respective ratings
    for (auto airline : routeVec)
    {
        std::cout << airline->getName() << ": ";
        for (auto stat : airline->getScores())
            std::cout << stat << ", ";
        std::cout << std::endl;
    }

    return 0;
}