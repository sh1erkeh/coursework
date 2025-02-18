#pragma once

#include "graph.hpp"

#include <vector>

namespace clrAlgo {


template<typename ColorChooser>
std::vector<unsigned> DSaturation(UndirectedGraph& graph) {
    // TODO: check template parameters

    // Stores information about each vertex
    struct Node {
        size_t index;
        
        // Number of different colors among neighbours
        size_t saturationDegree;

        // Number of uncolored neighbours
        size_t uncoloredDegree;

        Node() = default;
        Node(size_t index, size_t saturationDegree, size_t uncoloredDegree)
                : index{index}, saturationDegree{saturationDegree}, uncoloredDegree{uncoloredDegree}
            {}

        bool operator<(const Node& rhs) const {
            return std::tie(saturationDegree, uncoloredDegree, index)
                 > std::tie(rhs.saturationDegree, rhs.uncoloredDegree, rhs.index);
        }
    };

    // Color of each vertex
    std::vector<unsigned> color(graph.numberOfVertices);

    // Number of uncolored neighbours of each vertex
    std::vector<size_t> uncoloredDegree(graph.numberOfVertices);
    
    // Set of adjacent colors for each vertex
    // Potential std::bad_alloc
    std::vector<std::set<unsigned>> adjacentColors(graph.numberOfVertices);
 
    // Priority queue for finding minimal vertex
    std::set<Node> queue; 

    // Stores additional information needed to determine color 
    ColorChooser chooser(graph.numberOfVertices);

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
        color[vertex] = chooser(graph, vertex);

        // Update neighbours' data
        for (size_t neighbour : graph.adjacencyList[vertex]) {
            // If neighbour is already colored we don't need to update its data  
            if (color[neighbour] == 0) {
                // Delete old data
                queue.erase(Node{neighbour, adjacentColors[neighbour].size(), uncoloredDegree[neighbour]});

                // Update data
                adjacentColors[neighbour].insert(color[vertex]);
                uncoloredDegree[neighbour]--;

                // Insert updated data
                queue.insert(Node{neighbour, adjacentColors[neighbour].size(), uncoloredDegree[neighbour]});
            }
        }
    }

    return color;
}


}
