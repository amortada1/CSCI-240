#include <iostream>

#include "problem.h"
#include "uniform_cost_search.h"

int main(int argc, char const *argv[])
{
    UniformCostSearch ucs;
    Problem p;

    std::vector<State> path{ucs.start(p)};

    for (auto &&i : path) std::cout << i << std::endl << std::endl;
    
    return 0;
}
