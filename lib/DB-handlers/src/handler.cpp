// TODO: add exception safety 
#include "../include/handler.hpp"

#include <iostream>

Handler& Handler::Instance(const char* db_name) {
    static Handler inst(db_name);
    return inst;
}

int Handler::log(void* data, int argc, char** argv, char** colName) {
    std::cerr << static_cast<const char*>(data) << ":\n";
    for (size_t i = 0; i < argc; i++) {
        std::cerr << colName[i] << " = " << (argv[i] ? argv[i] : "NULL") << '\n';
    }
    std::cerr << std::endl;
    return 0;
}

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

void Handler::execute(const char* query) {
    char* errorMsg;
    const char* data = "Callback function called";

    // TODO: remove bad c-style cast
    if (sqlite3_exec(DB, query, &log, (void*)data, &errorMsg) != SQLITE_OK) {
        std::cerr << "SQL error: " << errorMsg << std::endl;
        sqlite3_free(errorMsg);
    } else {
        std::cerr << "Query executed successfully" << std::endl;
    } 
}

