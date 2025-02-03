#include "../include/colorChooser1.hpp"

ColorChooser::Node::Node(unsigned color, unsigned canBeColored, unsigned areColored)
    : color{color}, canBeColored{canBeColored}, areColored(areColored) {}

bool ColorChooser::Node::operator<(const Node& rhs) const {
    return std::tie(canBeColored, areColored, color)
         < std::tie(rhs.canBeColored, rhs.areColored, rhs.color);
}

ColorChooser::ColorChooser(clrAlgo::UndirectedGraph& graph) {
    n = graph.numberOfVertices;
    for (unsigned i = 0; i < n; i++) {
        colorData.insert(Node{i, static_cast<unsigned>(n), 0});
    }
}

int ColorChooser::operator()(clrAlgo::UndirectedGraph& graph, size_t vertex,
                             std::vector<std::set<unsigned>>& adjacentColors) {
    // Choose best color 
    auto best = colorData.begin();
    for (; best != colorData.end(); best++) {
        // If no neighbour has the same color as best->color
        if (adjacentColors[vertex].find(best->color) == adjacentColors[vertex].end()) {
            break;
        }
    }
    colorData.erase(colorData.begin());
    
    // Update color's data
    Node updC{best->color, best->canBeColored, best->areColored + 1};

    for (size_t neighbour : graph.adjacencyList[vertex]) {
        // If our neighbour could have been colored in <color> before, now it can't be
        if (adjacentColors[neighbour].find(best->color) == adjacentColors[neighbour].end()) {
            updC.canBeColored--;
        }
    }
    
    // Insert updated data 
    colorData.insert(updC);

    return best->color;
}
