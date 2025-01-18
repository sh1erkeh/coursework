#include "../include/coloring-algorithms.h"

#include <tuple>

namespace galgo {

NodeInfo::NodeInfo(size_t index, size_t saturationDegree, size_t uncoloredDegree)
    : index{index}, saturationDegree{saturationDegree}, uncoloredDegree{uncoloredDegree} {}

// 1) Compare saturationDegree
// 2) Compare uncoloredDegree
// 3) Compare index
bool NodeInfo::operator<(const NodeInfo &rhs) const {
    return std::tie(this->saturationDegree, this->uncoloredDegree, this->index)
           > std::tie(rhs.saturationDegree, rhs.uncoloredDegree, rhs.index);
}

std::vector<int> DSaturation(Graph *graph) {
    std::vector<int> color(graph->numberOfVertices, -1);
    std::vector<size_t> uncoloredDegree(graph->numberOfVertices);

    std::vector<std::set<int>> adjacentColors(graph->numberOfVertices);
    std::set<NodeInfo> queue; // Priority queue for finding minimal vertex

    // Find first available color
    auto firstFreeColor = [&](size_t vertex) -> int {
        int color = 0;
        for (auto it = adjacentColors[vertex].begin(); it != adjacentColors[vertex].end(); it++) {
            if (*it != color++) {
                break;
            }
        }
        return color;
    };

    // Add vertices to queue
    for (size_t vertex = 0; vertex < graph->numberOfVertices; vertex++) {
        uncoloredDegree[vertex] = graph->adjacencyList[vertex].size();
        queue.insert(NodeInfo{vertex, 0, uncoloredDegree[vertex]});
    }
 
    while (!queue.empty()) {
        // Extract minimal vertex
        size_t vertex = (*queue.begin()).index;
        queue.erase(queue.begin());

        // Color extracted vertex
        color[vertex] = firstFreeColor(vertex);

        // Update neighbours
        for (size_t neighbour : graph->adjacencyList[vertex]) {
            if (color[neighbour] == -1) {
                queue.erase(NodeInfo{neighbour, adjacentColors[neighbour].size(), uncoloredDegree[neighbour]});
                adjacentColors[neighbour].insert(color[vertex]);
                uncoloredDegree[neighbour]--;
                queue.insert(NodeInfo{neighbour, adjacentColors[neighbour].size(), uncoloredDegree[neighbour]});
            }
        }
    }

    return color;
}

}
