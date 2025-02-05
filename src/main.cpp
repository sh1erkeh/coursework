#include <iostream>

#include "graph.hpp"
#include "degree-saturation.hpp"
#include "../include/colorChooser1.hpp"

struct S {};

int main(int argc, char** argv) {
    clrAlgo::UndirectedGraph g{4};
    g.addEdge(0, 1);
    g.addEdge(1, 2);
    g.addEdge(2, 3);


    std::vector<unsigned> ans = clrAlgo::DSaturation<ColorChooser>(g);
    for (int i = 0; i < 4; i++) {
        std::cout << ans[i] << ' ';
    }
    std::cout << std::endl;
}
