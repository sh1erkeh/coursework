#include "handler.hpp"

#include <iostream>

struct Log {
    static int operator()(void* data, int argc, char** argv, char** colName) {
        std::cerr << static_cast<const char*>(data) << ":\n";
        for (int i = 0; i < argc; i++) {
            std::cerr << colName[i] << " = " << (argv[i] ? argv[i] : "NULL") << '\n';
        }
        std::cerr << std::endl;
        return 0;
    }
};
int main() {
    Handler<Log>& h = Handler<Log>::Instance("test.db");
    const char* sql = "CREATE TABLE COMPANY("  \
      "ID INT PRIMARY KEY     NOT NULL," \
      "NAME           TEXT    NOT NULL," \
      "AGE            INT     NOT NULL," \
      "ADDRESS        CHAR(50)," \
      "SALARY         REAL );";
    h.execute(sql);
    sql = "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY) "  \
         "VALUES (1, 'Paul', 32, 'California', 20000.00 ); " \
         "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY) "  \
         "VALUES (2, 'Allen', 25, 'Texas', 15000.00 ); "     \
         "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY)" \
         "VALUES (3, 'Teddy', 23, 'Norway', 20000.00 );" \
         "INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY)" \
         "VALUES (4, 'Mark', 25, 'Rich-Mond ', 65000.00 );";
    h.execute(sql);
    sql = "SELECT * from COMPANY";
    h.execute(sql);
}
