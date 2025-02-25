#include "../include/users-db-handler.hpp"
#include <stdexcept>

DatabaseManager& DatabaseManager::instance() {
    static DatabaseManager instance;
    return instance;
}

DatabaseManager::~DatabaseManager() {
    db.close();
}

DatabaseManager::DatabaseManager() {
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("users.db");

    if (!db.open()) {
        throw std::runtime_error("Could not create users.db");
    }

    QSqlQuery query;
    query.exec("CREATE TABLE IF NOT EXISTS users ("
               "id INTEGER PRIMARY KEY AUTOINCREMENT, "
               "login TEXT UNIQUE NOT NULL, "
               "password TEXT NOT NULL)");
}

void DatabaseManager::registerUser(const QString& login, const QString& password) {
    QSqlQuery query;
    query.prepare("INSERT INTO users (login, password) VALUES (:login, :password)");
    query.bindValue(":login", login);
    query.bindValue(":password", password);

    if (!query.exec()) {
        throw std::runtime_error("Error: Could not register user");
    }
}

bool DatabaseManager::validateUser(const QString& login, const QString& password) {
    QSqlQuery query;
    query.prepare("SELECT * FROM users WHERE login = :login AND password = :password");
    query.bindValue(":login", login);
    query.bindValue(":password", password);

    if (!query.exec()) {
        throw std::runtime_error("Error: could not validate user");
    }

    return query.next();
}
