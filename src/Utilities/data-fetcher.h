#pragma once

#include "graph.hpp"

#include <QVector>
#include <QString>

struct Event {
    QString subject_name;
    int group_name;

    Event(const QString&, int);
};

bool conflict(const Event&, const Event&);

QVector<Event> fetchEvents(const QString&);

clrAlgo::UndirectedGraph constructGraph(const QVector<Event>&);
