#include <iostream>
#include "Processor.h"

int main()
{
    Processor* prog = new Processor();

    prog->start();
    std::pair<double, double> timePair = prog->setRouteVec("Chicago", "Atlanta");
    std::cout << "Time (Map): " << timePair.first << std::endl;
    std::cout << "Time (Tree): " << timePair.second << std::endl;

    for (auto airline : prog->getRouteVec())
    {
        std::cout << airline->getName() << ": ";
        for (auto stat : airline->getScores())
            std::cout << stat << ", ";
        std::cout << std::endl;
    }

    return 0;
}