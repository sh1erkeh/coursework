#include "data-fetcher.h"

#include <qlogging.h>
#include <qsqldatabase.h>
#include <qsqlquery.h>

#include <QtSql>
#include <iostream>

Event::Event(QString subject_name, int group_name)
    : subject_name{std::move(subject_name)}, group_name{group_name} {}

auto confict(const Event& lhs, const Event& rhs) -> bool {
    return lhs.subject_name == rhs.subject_name ||
           lhs.group_name == rhs.group_name;
}

auto fetchEvents(int number_of_groups, const QVector<std::pair<QString, int>>& data) -> QVector<Event> {
    QVector<Event> events;
    for (const auto& p : data) {
        for (int i = 0; i < number_of_groups; i++) {
            for (int j = 0; j < p.second; j++) {
                events.push_back(Event{p.first, i});
            }
        }
    }
    return events;
}

auto constructGraph(const QVector<Event>& events) -> clrAlgo::UndirectedGraph {
    size_t eventsSize = events.size();
    clrAlgo::UndirectedGraph graph{eventsSize};

    for (size_t i = 0; i < eventsSize; i++) {
        for (size_t j = i + 1; j < eventsSize; j++) {
            if (confict(events[i], events[j])) {
                graph.addEdge(i, j);
            }
        }
    }

    std::cout << "constructed graph\n";
    return graph;
}
