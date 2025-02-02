#pragma once

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

        bool operator<(const Node& rhs) const;
    };

    size_t n; 
    std::set<Node> colorData;
public:
    // Constructor
    ColorChooser(clrAlgo::UndirectedGraph& graph); 
    
    // Needed to choose color
    int operator()(clrAlgo::UndirectedGraph& graph, size_t vertex,
                   std::vector<std::set<unsigned>>& adjacentColors);
};
