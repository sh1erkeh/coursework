#include "degree-saturation.hpp"
#include "tabu-search.hpp"
#include "graph.hpp"
#include "../include/dsatur-util.hpp"
#include "../include/tabu-search-util.hpp"

#include <iostream>

int log(void* data, int argc, char** argv, char** colName) {
    std::cerr << static_cast<const char*>(data) << ":\n";
    for (int i = 0; i < argc; i++) {
        std::cerr << colName[i] << " = " << (argv[i] ? argv[i] : "NULL") << '\n';
    }
    std::cerr << std::endl;
    return 0;
}

using clrAlgo::UndirectedGraph;

int main() {
    UndirectedGraph g{8};

    g.addEdge(0, 1);
    g.addEdge(1, 2);
    g.addEdge(1, 6);
    g.addEdge(2, 4);
    g.addEdge(4, 3);
    g.addEdge(4, 5);
    g.addEdge(4, 7);
    g.addEdge(7, 5);
    g.addEdge(5, 6);
    g.addEdge(3, 5);

    std::vector<unsigned> coloring = clrAlgo::DSaturation<ColorChooser>(g);
    for (size_t i = 0; i < g.numberOfVertices; i++) {
        std::cout << coloring[i] << ' ';
    }
    std::cout << std::endl;


    clrAlgo::tabuSearch<ObjectiveFunction, GetNeighbours>(g, coloring, 1000, 10);

    for (size_t i = 0; i < g.numberOfVertices; i++) {
        std::cout << coloring[i] << ' ';
    }
    std::cout << std::endl;

    return 0;
}
