#pragma once

#include <vector>
#include <limits>
#include <algorithm>

// #include "utility.hpp"

template<typename ObjectiveFunction, typename GetNeighbours>
void tabuSearch(std::vector<unsigned>& solution, unsigned maxIter, size_t tabuListSize) {
    // TODO: write concepts for template arguments
    std::vector<unsigned> current_solution(solution);
    std::vector<std::vector<unsigned>> tabuList;

    for (unsigned iter = 0; iter < maxIter; ++iter) {
        std::vector<std::vector<unsigned>> neighbours = GetNeighbours(current_solution);

        std::vector<unsigned> best_neighbour;
        int best_neighbour_fitness = std::numeric_limits<int>::max();

        for (const auto& neighbour : neighbours) {
            if (std::find(tabuList.begin(), tabuList.end(), neighbour) == tabuList.end()) {
                int neighbour_fitness = ObjectiveFunction(neighbour);
                if (neighbour_fitness < best_neighbour_fitness) {
                    best_neighbour = neighbour;
                    best_neighbour_fitness = neighbour_fitness;
                }
            }
        }

        if (best_neighbour.empty()) {
            break;
        }

        current_solution = best_neighbour;
        tabuList.push_back(best_neighbour);
        if (tabuList.size() > tabuListSize) {
            // Remove the oldest entry from the
            // tabu list if it exceeds the size
            tabuList.erase(tabuList.begin());
        }

        if (ObjectiveFunction(best_neighbour) < ObjectiveFunction(solution)) {
            solution = best_neighbour;
        }
    }
}
