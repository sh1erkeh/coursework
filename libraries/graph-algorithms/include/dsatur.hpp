#pragma once

#include "graph.hpp"
#include <vector>

namespace clrAlgo {

template<typename Cache, typename ChooseColor>
std::vector<int> DSaturation(Graph& graph) {
    // Stores information about each vertex
    struct Node {
        size_t index,
               saturationDegree, // Number of different colors among neighbours
               uncoloredDegree; // Number of uncolored neighbours

        Node() = default;
        Node(size_t index, size_t saturationDegree, size_t degree);

        bool operator<(const Node& rhs) const;
    };

    // Color of each vertex
    std::vector<int> color(graph.numberOfVertices, -1);

    // Number of uncolored neighbours of each vertex
    std::vector<size_t> uncoloredDegree(graph.numberOfVertices);
    
    // Set of adjacent colors for each vertex
    std::vector<std::set<int>> adjacentColors(graph.numberOfVertices);
 
    // Priority queue for finding minimal vertex
    std::set<Node> queue; 

    // Cache stores additional information needed to determine color 
    Cache cache(graph.numberOfVertices);

    // Add vertices to queue
    for (size_t vertex = 0; vertex < graph.numberOfVertices; vertex++) {
        uncoloredDegree[vertex] = graph.adjacencyList[vertex].size();
        queue.insert(Node{vertex, 0, uncoloredDegree[vertex]});
    }
 
    while (!queue.empty()) {
        // Extract minimal vertex
        size_t vertex = (*queue.begin()).index;
        queue.erase(queue.begin());

        // Color extracted vertex
        color[vertex] = ChooseColor(cache, vertex);

        // Update neighbours' data
        for (size_t neighbour : graph.adjacencyList[vertex]) {
            // If neighbour is already colored we don't need to update its data  
            if (color[neighbour] == -1) {
                // Delete old data
                queue.erase(Node{neighbour, adjacentColors[neighbour].size(), uncoloredDegree[neighbour]});

                // Update data
                adjacentColors[neighbour].insert(color[vertex]);
                uncoloredDegree[neighbour]--;

                // Insert updated data
                queue.insert(Node{neighbour, adjacentColors[neighbour].size(), uncoloredDegree[neighbour]});

                // Update cache 
                cache.update(color, uncoloredDegree, adjacentColors);
            }
        }
    }

    return color;
}

}
