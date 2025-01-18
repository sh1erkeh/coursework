#pragma once

#include "graph.h"
#include <vector>

namespace galgo {

// Information about each vertex
class NodeInfo {
public:
    size_t index,
           saturationDegree, // Number of different colors among neighbours
           uncoloredDegree; // Number of uncolored neighbours

    NodeInfo() = default;
    NodeInfo(size_t index, size_t saturationDegree, size_t degree);

    bool operator<(const NodeInfo& rhs) const;
};

std::vector<int> DSaturation(Graph* graph);

}
