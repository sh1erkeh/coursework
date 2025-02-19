#include "../include/handler.hpp"

#include <iostream>

namespace dbHandl {


Handler::Handler(const char* db_name) {
    if (sqlite3_open(db_name, &DB)) {
        std::cerr << "Can't open database: " << sqlite3_errmsg(DB) << std::endl;
    } else {
        std::cerr << "Opened database successfully" << std::endl;
    }
} 

Handler::~Handler() {
    sqlite3_close(DB);
}

Handler& Handler::Instance(const char* db_name) {
    static Handler inst(db_name);
    return inst;
}

void Handler::execute(const char* query, int (*f)(void*, int, char**, char**)) {
    char* errorMsg;

    // TODO: remove bad c-style cast
    if (sqlite3_exec(DB, query, f, nullptr, &errorMsg) != SQLITE_OK) {
        std::cerr << "SQL error: " << errorMsg << std::endl;
        sqlite3_free(errorMsg);
    } else {
        std::cerr << "Query executed successfully" << std::endl;
    } 
}


}
