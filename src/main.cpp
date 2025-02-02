#include "graph.hpp"
#include "degreeSaturation.hpp"
#include "../include/colorChooser1.hpp"

#include <iostream>

int main() {
    clrAlgo::UndirectedGraph g{4};
    g.addEdge(0, 1);
    g.addEdge(1, 2);
    g.addEdge(2, 3);
    
    std::vector<unsigned> coloring = clrAlgo::DSaturation<ColorChooser>(g);
    for (size_t i = 0; i < 4; i++) {
        std::cout << coloring[i] << ' ';
    }
    std::cout << '\n';
}
