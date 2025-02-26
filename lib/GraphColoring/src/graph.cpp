#include "../include/graph.hpp"

#include <algorithm>

namespace clrAlgo {


Graph::Graph(size_t numberOfVertices, std::vector<std::set<size_t>>& adjacencyList) {
    this->numberOfVertices = numberOfVertices;
    std::copy(adjacencyList.begin(), adjacencyList.end(), std::back_inserter(this->adjacencyList));
}

Graph::Graph(size_t numberOfVertices) {
    this->numberOfVertices = numberOfVertices;
    adjacencyList.assign(numberOfVertices, std::set<size_t>());
}

void Graph::addEdge(size_t from, size_t to) {
    adjacencyList[from].insert(to);
}

void UndirectedGraph::addEdge(size_t from, size_t to) {
    adjacencyList[from].insert(to);
    adjacencyList[to].insert(from); 
}


}
