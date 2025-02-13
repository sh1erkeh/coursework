#pragma once

#include "graph.hpp"

#include <cstddef>
#include <string>
#include <vector>

struct Lesson {
    size_t lessonIndex;
    std::string name;
    std::string teacher;
};

struct Event: public Lesson {
    size_t eventIndex;
    std::string group;
};

void readDataFromDB(std::vector<Event>&);

void constructConflictsGraph(clrAlgo::UndirectedGraph&, std::vector<Event>&);

