#include <stdio.h>
#include <stdlib.h>
#include "sqllite/sqlite3.h"
#include <iostream>
#include <string>


static int callback(void* NotUsed, int argc, char** argv, char** azColName) {
    int i;

    for (i = 0; i < argc; i++) {
        std::cout << argv[i] << std::endl;
    }

    std::cout << "\n" << std::endl;

    return 0;
}


bool add_virus(std::string hash_of_exe) {
    sqlite3* db;
    char* err_msg = 0;
    int rc;
    std::string sql;

    rc = sqlite3_open("virus_test_database.db", &db);

    if (rc) {
        std::cout << "Error: DATABASE NOT OPEN" << std::endl;
        return false;
    }
    else {
        std::cout << "DATABASE WAS OPENED" << std::endl;
    }

    sql = "INSERT INTO viruses (id, name, hash) VALUES (1, 'addedByUser', '" + hash_of_exe + "');";
    std::cout << sql << std::endl;
    rc = sqlite3_exec(db, const_cast<char*>(sql.c_str()), callback, 0, &err_msg);
    std::cout << err_msg << std::endl;
    if (rc != SQLITE_OK) {
        std::cout << "Error: EXEC NOT SUCCESS" << std::endl;
        sqlite3_free(err_msg);
    }
    else {
        std::cout << "EXEC SUCCESS" << std::endl;
    }

    sqlite3_close(db);
    
    return true;
}


int main(int argc, char** argv) {
    if (add_virus("blablahash")) {
        std::cout << "READY" << std::endl;
    }
    else {
        std::cout << "ERROR" << std::endl;
    }

    return 0;
}
