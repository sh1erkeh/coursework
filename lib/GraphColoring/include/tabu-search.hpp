#pragma once

#include <algorithm>
#include <limits>
#include <vector>

#include "graph.hpp"

namespace clrAlgo {

template <typename ObjectiveFunction, typename GetNeighbours>
void tabuSearch(const UndirectedGraph& graph, std::vector<unsigned>& coloring,
                unsigned maxIter, size_t tabuListSize) {
    // TODO: write concepts for template arguments

    constexpr std::pair<size_t, unsigned> NOT_FOUND = {-1, -1};
    ObjectiveFunction func;
    GetNeighbours neigh;

    std::vector<unsigned> current_solution(coloring);
    std::vector<std::pair<size_t, unsigned>> tabuList;

    for (unsigned iter = 0; iter < maxIter; ++iter) {
        std::vector<std::pair<size_t, unsigned>> neighbours =
            neigh(graph, current_solution);

        std::pair<size_t, unsigned> best_neighbour = NOT_FOUND;
        int best_neighbour_fitness = std::numeric_limits<int>::max();

        for (const auto& neighbour : neighbours) {
            if (std::find(tabuList.begin(), tabuList.end(), neighbour) ==
                tabuList.end()) {
                unsigned old = current_solution[neighbour.first];
                current_solution[neighbour.first] = neighbour.second;

                int neighbour_fitness = func(current_solution);

                current_solution[neighbour.first] = old;

                if (neighbour_fitness < best_neighbour_fitness) {
                    best_neighbour = neighbour;
                    best_neighbour_fitness = neighbour_fitness;
                }
            }
        }

        if (best_neighbour == NOT_FOUND) {
            break;
        }

        current_solution[best_neighbour.first] = best_neighbour.second;
        tabuList.push_back(best_neighbour);

        if (tabuList.size() > tabuListSize) {
            tabuList.erase(tabuList.begin());
        }

        if (func(current_solution) < func(coloring)) {
            coloring = current_solution;
        }
    }
}

}  // namespace clrAlgo
