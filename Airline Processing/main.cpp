#include <iostream>
#include <iomanip>
#include <string>
#include "Processor.h"

int main()
{
    Processor* prog = new Processor();

    prog->start();
    std::pair<double, double> timePair = prog->setRouteVec("Johannesburg", "Paris");
    std::cout << "Time (Map): " << timePair.first << std::endl;
    std::cout << "Time (Tree): " << timePair.second << std::endl;

    auto routeVec = prog->getRouteVec();

    std::cout << std::fixed << std::setprecision(1) << std::endl;
    for (auto airline : routeVec)
    {
        std::cout << airline->getName() << ": ";
        for (auto stat : airline->getScores())
            std::cout << stat << ", ";
        std::cout << std::endl;
    }

    return 0;
}