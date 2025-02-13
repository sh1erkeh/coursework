#include "../include/color-chooser.hpp"
#include "../include/prepare-data.hpp"
#include "graph.hpp"

#include <iostream>

int main(int argc, char** argv) {
    // db stuff
    
    std::vector<Event> events;
    readDataFromDB(events);

    clrAlgo::UndirectedGraph conflictsGraph{events.size()};
    constructConflictsGraph(conflictsGraph, events);
}
