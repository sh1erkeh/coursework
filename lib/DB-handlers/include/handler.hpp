#pragma once

#include <sqlite3.h>

class Handler {
private:
    sqlite3* DB;
    static int log(void*, int, char**, char**);

    Handler(const char*);
    ~Handler();

    Handler(const Handler&) = delete;
    Handler& operator=(const Handler&) = delete;
public:
    static Handler& Instance(const char*);

    void execute(const char*);
};

