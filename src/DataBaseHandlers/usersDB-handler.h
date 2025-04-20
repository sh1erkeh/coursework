#pragma once

#include <QDebug>
#include <QObject>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

class DatabaseManager : public QObject {
    Q_OBJECT
public:
    static auto instance() -> DatabaseManager&;

    void initDatabase();

    void registerUser(const QString&, const QString&);

    auto validateUser(const QString&, const QString&) -> bool;

    DatabaseManager(const DatabaseManager&) = delete;
    auto operator=(const DatabaseManager&) -> DatabaseManager& = delete;

private:
    DatabaseManager();
    ~DatabaseManager() override;

    QSqlDatabase db;
};
