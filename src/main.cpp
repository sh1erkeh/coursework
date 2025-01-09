#include <iostream>
#include <vector>

#include "graph.h"
#include "coloring-algorithms.h"

using namespace galgo;

int main() {
    Graph *g = new Graph{2};
    g->addEdge(0, 1);

    std::vector<int> a = DSaturation(g);
    for (size_t i = 0; i < 2; i++) {
        std::cout << a[i] << ' ';
    }
    std::cout << std::endl;

    return 0;
}
