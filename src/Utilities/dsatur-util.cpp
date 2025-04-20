#include "dsatur-util.h"

ColorChooser::Node::Node(unsigned color, unsigned canBeColored,
                         unsigned areColored)
    : color{color}, canBeColored{canBeColored}, areColored(areColored) {}

auto ColorChooser::Node::operator<(const Node& rhs) const -> bool {
    return std::tie(canBeColored, areColored, color) <
           std::tie(rhs.canBeColored, rhs.areColored, rhs.color);
}

ColorChooser::ColorChooser(size_t numberOfVertices) {
    n = numberOfVertices;
    for (unsigned i = 0; i < n; i++) {
        colorData.insert(Node{i, static_cast<unsigned>(n), 0});
    }
    adjacentColors.assign(n, std::set<unsigned>());
}

auto ColorChooser::operator()(const clrAlgo::UndirectedGraph& graph,
                              size_t vertex) -> unsigned {
    auto presentAmongNeighbours = [&](size_t vertex, unsigned color) {
        if (adjacentColors[vertex].find(color) ==
            adjacentColors[vertex].end()) {
            return false;
        } else {
            return true;
        }
    };

    // Choose best color
    auto best = colorData.begin();

    for (;
         best != colorData.end() && presentAmongNeighbours(vertex, best->color);
         best++);
    colorData.erase(colorData.begin());

    // Update color's data
    Node updC{best->color, best->canBeColored, best->areColored + 1};

    for (size_t neighbour : graph.adjacencyList[vertex]) {
        // If our neighbour could have been colored in <color> before, now it
        // can't be
        if (!presentAmongNeighbours(neighbour, best->color)) {
            updC.canBeColored--;
            adjacentColors[neighbour].insert(best->color);
        }
    }
    // Insert updated data
    colorData.insert(updC);

    return best->color;
}
