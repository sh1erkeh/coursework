#include <iostream>
#include <vector>
#include <set>

#include "graph.h"
#include "coloring-algorithms.h"

using galgo::Graph, galgo::DSaturation;

int main() {
    size_t n, m;
    std::cin >> n >> m;

    std::vector<std::set<size_t>> adj(n);
    for (size_t i = 0; i < m; i++) {
        size_t u, v;
        std::cin >> u >> v;
        adj[u].insert(v);
        adj[v].insert(u);
    }

    Graph *g = new Graph{n, adj};

    std::vector<int> a = DSaturation(g);
    for (size_t i = 0; i < n; i++) {
        std::cout << a[i] << ' ';
    }
    std::cout << std::endl;

    return 0;
}
