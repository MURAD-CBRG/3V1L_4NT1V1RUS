#include <stdio.h>
#include <stdlib.h>
#include "sqllite/sqlite3.h" 
#include <iostream>
#include <string>


static int callback(void* data, int argc, char** argv, char** azColName) {
    int i;

    for (i = 0; i < argc; i++) {
        std::cout << argv[i] << std::endl;
    }

    std::cout << "\n" << std::endl;

    return 0;
}


bool delete_virus(std::string hash_of_exe) {
    sqlite3* db;
    char* err_msg = 0;
    int rc;
    std::string sql;
    const char* data = "SUCCESS OF EXECUTION OF THE FUNC";

    rc = sqlite3_open("virus_test_database.db", &db);

    if (rc) {
        std::cout << "Error: DATABASE NOT OPEN" << std::endl;

        return false;
    }
    else {
        std::cout << "DATABASE WAS OPENED" << std::endl;
    }

    sql = "DELETE FROM viruses WHERE hash='" + hash_of_exe + "'";

    rc = sqlite3_exec(db, const_cast<char*>(sql.c_str()), callback, (void*)data, &err_msg);

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
    if (delete_virus("blablahash")) {
        std::cout << "SUCCESS DELETE" << std::endl;
    }
    else {
        std::cout << "ERROR" << std::endl;
    }

    return 0;
}
