#include "data-fetcher.h"

#include <QtSql>
#include <iostream>
#include <qlogging.h>
#include <qsqldatabase.h>
#include <qsqlquery.h>
#include <stdexcept>

Event::Event(const QString& subject_name, int group_name)
        : subject_name{subject_name}, group_name{group_name}
    {}

bool confict(const Event& lhs, const Event& rhs) {
    return lhs.subject_name == rhs.subject_name ||
           lhs.group_name == rhs.group_name;
}

QVector<Event> fetchEvents(const QString& login) {
    qDebug() << "Started fetching";

    QSqlDatabase db = QSqlDatabase::database();

    if (!db.open()) {
        throw std::runtime_error("Failed to connect to database");
    }
   
    QMap<QString, int> subjects;
    QSqlQuery subjectQuery(db);

    subjectQuery.exec("SELECT * FROM SUBJECTS");

    qDebug() << "SUBJECTS:";
    while (subjectQuery.next()) {
        qDebug() << subjectQuery.value("name").toString();
        subjects[subjectQuery.value("name").toString()] = subjectQuery.value("id").toInt();
    }

    QVector<Event> events;
    QSqlQuery groupQuery("SELECT * FROM GROUPS");
    
    qDebug() << "GROUPS:";
    while (groupQuery.next()) {
        QString group_name;
        QString subject_ids_str;
        QString quantities_str;
        int amount;

        try {
            amount = groupQuery.value("amount").toInt();
            group_name = groupQuery.value("name").toString();
            subject_ids_str = groupQuery.value("subjects").toString();
            quantities_str = groupQuery.value("quantities").toString();
        } catch (...) {
            throw std::runtime_error("Error fetching data");
        }

        qDebug() << amount;
        qDebug() << group_name;
        qDebug() << subject_ids_str;
        qDebug() << quantities_str;

        QStringList subject_ids = subject_ids_str.split(',');
        QStringList quantities = quantities_str.split(',');

        for (int i = 0; i < subject_ids.size(); ++i) {
            QString subject_id = subject_ids[i];
            int attendance = quantities[i].toInt();

            if (!subjects.contains(subject_id)) {
                throw std::logic_error("No such subject");
            }

            for (int group_number = 0; group_number < amount; group_number++) {
                for (int j = 0; j < attendance; ++j) {
                    events.append(Event{subject_id, group_number});
                }
            }
        }
    }

    db.close();
    return events;
}

clrAlgo::UndirectedGraph constructGraph(const QVector<Event>& events) {
    size_t eventsSize = events.size();
    std::cout << events.size() << '\n';
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
