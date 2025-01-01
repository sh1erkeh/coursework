#include "graph.h"
#include <algorithm>
#include <stdexcept>

Graph::Graph(size_t numberOfVertices, std::vector<std::set<size_t>> &adjacencyList) {
    this->numberOfVertices = numberOfVertices;
    std::copy(adjacencyList.begin(), adjacencyList.end(), std::back_inserter(this->adjacencyList));
}

Graph::Graph(size_t numberOfVertices) {
    this->numberOfVertices = numberOfVertices;
    this->adjacencyList.assign(numberOfVertices, std::set<size_t>());
}

void Graph::addEdge(size_t from, size_t to) {
    if (from == to) {
        throw std::invalid_argument("Graph::addEdge arguments cannot be equal");
    }
    this->adjacencyList[from].insert(to);
}