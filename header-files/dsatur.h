#ifndef DSATUR
#define DSATUR

#include "graph.h"

// Information about each vertex
class Node {
public:
    size_t index,
           saturationDegree, // Number of different colors among neighbours
           uncoloredDegree; // Number of uncolored neighbours

    Node();
    Node(size_t index, size_t saturationDegree, size_t degree);

    bool operator<(const Node &lhs);
};

// 1) Find vertex with minimal (saturationDegree, uncoloredDegree)
// 2) Paint found vertex in minimal availiable color
void DSaturation(Graph *graph);

#endif