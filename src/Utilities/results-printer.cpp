#include "results-printer.h"
#include <QString>
#include <QFile>
#include <QTextStream>
#include <map>
#include <qlogging.h>
#include <string>
#include <iostream>

const char* days = ";Понедельник;Вторник;Среда;Четверг;Пятница;Суббота";

void printEvents(const QVector<Event>& events, const std::vector<unsigned>& coloring) {
    std::map<int, QVector<std::pair<unsigned, QString>>> groupedData;
    for (int i = 0; i < events.size(); ++i) {
        groupedData[events[i].group_name].append({coloring[i], events[i].subject_name});
    }

    for (const auto& group : groupedData) {
        QString fileName = "Группа" + QString::fromStdString(std::to_string(group.first + 1) + ".csv");  
        QFile file(fileName);

        QString timetable[7][7]{};
        for (int i = 0; i < 7; i++) {
            timetable[i][0] = QString::fromStdString(std::to_string(i + 1));
        }

        for (const auto& pair : group.second) {
            // std::cout << (pair.first - 1) / 7 << ' ' << (pair.first - 1) % 7 << ' ' << pair.first - 1 << std::endl;
            timetable[(pair.first - 1) / 6][(pair.first - 1) % 6 + 1] = pair.second; 
        }

        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&file);
            out << days << '\n';
            // std::cout << days << '\n';
            for (int i = 0; i < 7; i++) {
                for (int j = 0; j < 6; j++) {
                    out << timetable[i][j] << ';';
                    // std::cout << timetable[i][j].toStdString() << ' ';
                }
                out << '\n';
                // std::cout << std::endl;
            } 
            file.close();
        } else {
            throw std::runtime_error("Could not open file for writing: " + fileName.toStdString());
        }
    }
}
