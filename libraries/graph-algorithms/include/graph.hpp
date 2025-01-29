#pragma once

#include <vector>
#include <set>

namespace clrAlgo {

// Basic undirected graph with no double edges
class Graph {
public:
    size_t numberOfVertices;
    std::vector<std::set<size_t>> adjacencyList;

    explicit Graph(size_t numberOfVertices);
    Graph(size_t numberOfVertices, std::vector<std::set<size_t>>& adjacencyList);

    // Graph is too heavy to copy
    Graph(const Graph&) = delete;
    Graph& operator=(const Graph&) = delete;

    // Adds directed edge
    void addEdge(size_t from, size_t to);
};

}
