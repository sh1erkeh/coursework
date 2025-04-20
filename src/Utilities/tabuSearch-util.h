#pragma once

#include <vector>

#include "graph.hpp"

struct ObjectiveFunction {
    auto operator()(const std::vector<unsigned>&) -> int;
};

struct GetNeighbours {
    auto operator()(const clrAlgo::UndirectedGraph&,
                    const std::vector<unsigned>&)
        -> std::vector<std::pair<size_t, unsigned>>;
};
