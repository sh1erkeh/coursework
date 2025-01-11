#pragma once

#include "graph.h"

namespace galgo {
    class Node;
}

// Information about each vertex
class Node {
public:
    size_t index,
           saturationDegree, // Number of different colors among neighbours
           uncoloredDegree; // Number of uncolored neighbours

    Node();
    Node(size_t index, size_t saturationDegree, size_t degree);

    // Not sure what "const bool" does
    bool operator<(const Node &rhs) const;
};

// 1) Find vertex with minimal (saturationDegree, uncoloredDegree)
// 2) Paint found vertex in minimal availiable color
std::vector<int> DSaturation(galgo::Graph *graph);
