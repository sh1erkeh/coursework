#pragma once

#include <set>
#include <vector>

#include "graph.hpp"

class ColorChooser {
private:
    struct Node {
        unsigned color;

        // Number of vertices that can be colored in <color>
        unsigned canBeColored;

        // Number of vertices that are colored in <color>
        unsigned areColored;

        Node(unsigned color, unsigned canBeColored, unsigned areColored);
        auto operator<(const Node& rhs) const -> bool;
    };

    size_t n;
    std::set<Node> colorData;
    std::vector<std::set<unsigned>> adjacentColors;

public:
    explicit ColorChooser(size_t n);

    // Choose color
    auto operator()(const clrAlgo::UndirectedGraph& graph, size_t vertex)
        -> unsigned;
};
