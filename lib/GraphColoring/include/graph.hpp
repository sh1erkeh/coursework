#pragma once

#include <vector>
#include <set>

namespace clrAlgo {


// Basic directed graph (no loops and no double edges)
class Graph {
public:
    size_t numberOfVertices;
    std::vector<std::set<size_t>> adjacencyList;

    explicit Graph(size_t numberOfVertices);
    Graph(size_t numberOfVertices, std::vector<std::set<size_t>>& adjacencyList);

    // Add directed edge
    virtual void addEdge(size_t from, size_t to);
};

// Basic undirected graph (no loops and no double edges)
class UndirectedGraph: public Graph {
public:
    // Inherit constructor
    using Graph::Graph;

    // Add undirected edge
    void addEdge(size_t from, size_t to) final;
};


}
