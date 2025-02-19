#pragma once

#include <sqlite3.h>

namespace dbHandl {


// TODO: make log templated, add exception safety
class Handler {
private:
    sqlite3* DB;

    Handler(const char*);
    ~Handler();

    Handler(const Handler&) = delete;
    Handler& operator=(const Handler&) = delete;
public:
    static Handler& Instance(const char*);

    void execute(const char*, int (*)(void*, int, char**, char**));
};


}
