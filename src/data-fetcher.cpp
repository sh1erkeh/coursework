#include "../include/data-fetcher.hpp"

#include <QtSql>
#include <stdexcept>

Event::Event(const QString& subject_name, const QString& group_name)
        : subject_name{subject_name}, group_name{group_name}
    {}

bool confict(const Event& lhs, const Event& rhs) {
    return lhs.subject_name == rhs.subject_name;
}

QVector<Event> fetchEvents() {
    QDir dir;
    QString path = dir.currentPath() + "/database";

    if (!dir.exists(path)) {
        dir.mkpath(path);
    }

    QString dbPath = path + "/data.db";

    QSqlDatabase db = QSqlDatabase::addDatabase(("QSQLITE"));
    db.setDatabaseName(dbPath);

    if (!db.open()) {
        throw std::runtime_error("Failed to connect to database");
    }
   
    QMap<int, QString> subjects;
    QSqlQuery subjectQuery("SELECT id, name FROM SUBJECTS");
    while (subjectQuery.next()) {
        subjects[subjectQuery.value("id").toInt()] = subjectQuery.value("name").toString();
    }

    QVector<Event> events;
    QSqlQuery groupQuery("SELECT name, subjects, quantities FROM GROUPS");

    while (groupQuery.next()) {
        QString group_name = groupQuery.value("name").toString();
        QString subject_ids_str = groupQuery.value("subjects").toString();
        QString quantities_str = groupQuery.value("quantities").toString();

        QStringList subject_ids = subject_ids_str.split(',');
        QStringList quantities = quantities_str.split(',');

        for (int i = 0; i < subject_ids.size(); ++i) {
            int subject_id = subject_ids[i].toInt();
            int attendance = quantities[i].toInt();

            if (!subjects.contains(subject_id)) {
                throw std::logic_error("No such subject");
            }

            for (int j = 0; j < attendance; ++j) {
                events.append(Event{subjects[subject_id], group_name});
            }
        }
    }

    db.close();
    return events;
}

clrAlgo::UndirectedGraph constructGraph(const QVector<Event>& events) {
    size_t eventsSize = events.size();
    clrAlgo::UndirectedGraph graph{eventsSize};

    for (size_t i = 0; i < eventsSize; i++) {
        for (size_t j = i + 1; j < eventsSize; j++) {
            if (confict(events[i], events[j])) {
                graph.addEdge(i, j);
            }
        }
    }

    return graph;
}
