#pragma once

#include <sqlite3.h>
#include <iostream>

template<typename Fetcher>
class Handler {
private:
    sqlite3* DB;

    Handler(const char* db_name) {
        if (sqlite3_open(db_name, &DB)) {
            std::cerr << "Can't open database: " << sqlite3_errmsg(DB) << std::endl;
        } else {
            std::cerr << "Opened database successfully" << std::endl;
        }
    }

    ~Handler() {
        sqlite3_close(DB);
    }

    Handler(const Handler&) = delete;
    Handler& operator=(const Handler&) = delete;
public:
    static Handler& Instance(const char* db_name) {
        static Handler inst(db_name);
        return inst;
    }

    void execute(const char* query) {
        char* errorMsg;
        const char* data = "Fetcher called";

        // TODO: remove bad c-style cast
        if (sqlite3_exec(DB, query, &Fetcher::operator(), (void*)data, &errorMsg) != SQLITE_OK) {
            std::cerr << "SQL error: " << errorMsg << std::endl;
            sqlite3_free(errorMsg);
        } else {
            std::cerr << "Query executed successfully" << std::endl;
        } 
    }
};

