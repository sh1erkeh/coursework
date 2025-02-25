#pragma once

#include "graph.hpp"

#include <QVector>
#include <QString>

struct Event {
    QString subject_name;
    QString group_name;

    Event(const QString&, const QString&);
};

bool conflict(const Event&, const Event&);

QVector<Event> fetchEvents();

clrAlgo::UndirectedGraph constructGraph(const QVector<Event>&);
