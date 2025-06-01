#pragma once

#include <QString>
#include <QVector>

#include "graph.hpp"

struct Event {
    QString subject_name;
    int group_name;

    Event(QString, int);
};

auto conflict(const Event&, const Event&) -> bool;

auto fetchEvents(int, const QVector<std::pair<QString, int>>&) -> QVector<Event>;

auto constructGraph(const QVector<Event>&) -> clrAlgo::UndirectedGraph;
