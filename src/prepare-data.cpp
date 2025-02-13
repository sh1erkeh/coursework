#include "../include/prepare-data.hpp"

#include <unordered_map>

void constructConflictsGraph(clrAlgo::UndirectedGraph& graph, std::vector<Event>& events) {
    std::unordered_map<size_t, std::vector<size_t>> conflicts;
    for (Event& e : events) {
        for (size_t idx : conflicts[e.lessonIndex]) {
            graph.addEdge(idx, e.eventIndex);
        }
        conflicts[e.lessonIndex].push_back(e.eventIndex);
    }
}
