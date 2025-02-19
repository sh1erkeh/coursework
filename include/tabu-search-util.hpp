#pragma once

#include <vector>

#include "graph.hpp"

struct ObjectiveFunction {
    int operator()(const std::vector<unsigned>&); 
};

struct GetNeighbours {
    std::vector<std::pair<size_t, unsigned>> operator()(const clrAlgo::UndirectedGraph&, const std::vector<unsigned>&);
};
