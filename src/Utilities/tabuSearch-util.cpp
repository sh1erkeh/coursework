#include "tabuSearch-util.h"

#include <algorithm>
#include <map>
#include <utility>

int ObjectiveFunction::operator()(const std::vector<unsigned>& coloring) {
    std::set<unsigned> temp(coloring.begin(), coloring.end());
    return static_cast<int>(temp.size());
}

std::vector<std::pair<size_t, unsigned>> GetNeighbours::operator()(
    const clrAlgo::UndirectedGraph& graph,
    const std::vector<unsigned>& coloring) {
    unsigned upper_limit = *std::max_element(coloring.begin(), coloring.end());
    std::vector<std::pair<size_t, unsigned>> result;

    for (size_t i = 0; i < graph.numberOfVertices; i++) {
        std::map<unsigned, bool> adjacentColors;

        for (size_t neighbour : graph.adjacencyList[i]) {
            adjacentColors[coloring[neighbour]] = true;
        }
        for (unsigned color = 1; color <= upper_limit; color++) {
            if (!adjacentColors[color]) {
                result.push_back(std::make_pair(i, color));
            }
        }
    }
    return result;
}
