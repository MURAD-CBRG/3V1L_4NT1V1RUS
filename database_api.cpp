#include <stdio.h>
#include <stdlib.h>
#include "sqllite/sqlite3.h"
#include <iostream>
#include <string>


static int callback(void* NotUsed, int argc, char** argv, char** azColName) {
    (*(bool*)NotUsed) = true;

    return 0;
}


//bool search_by_signature(std::string hash_of_exe) {
//    sqlite3* db;
//    int rc;  // commander of database
//    char* error_msg = 0;
//    std::string sql;
//    bool data = false;
//
//    rc = sqlite3_open("virus_test_database.db", &db);
//
//    if (rc) {
//        return false;
//    }
//
//    sql = "SELECT * FROM viruses WHERE hash='" + hash_of_exe + "'";
//
//    rc = sqlite3_exec(db, const_cast<char*>(sql.c_str()), callback, (void*)&data, &error_msg);
//
//    if (!data) {
//        return false;
//    }
//
//    if (rc != SQLITE_OK) {
//        sqlite3_free(error_msg);
//    }
//
//    sqlite3_close(db);
//
//    return true;
//}
//
//
//bool add_virus(std::string hash_of_exe) {
//    sqlite3* db;
//    char* err_msg = 0;
//    int rc;
//    std::string sql;
//
//    rc = sqlite3_open("virus_test_database.db", &db);
//
//    if (rc) {
//        return false;
//    }
//
//    sql = "INSERT INTO viruses (name, hash) VALUES ('addedByUser', '" + hash_of_exe + "');";
//    rc = sqlite3_exec(db, const_cast<char*>(sql.c_str()), callback, 0, &err_msg);
//
//    if (rc != SQLITE_OK) {
//        sqlite3_free(err_msg);
//    }
//
//    sqlite3_close(db);
//
//    return true;
//}
//
//
//
//bool delete_virus(std::string hash_of_exe) {
//    sqlite3* db;
//    char* err_msg = 0;
//    int rc;
//    std::string sql;
//    const char* data = "SUCCESS OF EXECUTION OF THE FUNC";
//
//    rc = sqlite3_open("virus_test_database.db", &db);
//
//    if (rc) {
//        return false;
//    }
//
//    sql = "DELETE FROM viruses WHERE hash='" + hash_of_exe + "'";
//
//    rc = sqlite3_exec(db, const_cast<char*>(sql.c_str()), callback, 0, &err_msg);
//
//    if (rc != SQLITE_OK) {
//        sqlite3_free(err_msg);
//    }
//
//    sqlite3_close(db);
//
//    return true;
//}


bool database_control(std::string hash_of_exe, std::string action) {
    sqlite3* db;
    char* err_msg = 0;
    int rc{ sqlite3_open("virus_test_database.db", &db) };
    std::string sql;
    
    if (rc) {
        return false;
    }

    if (action == "FIND") {
        bool data = false;
        sql = "SELECT * FROM viruses WHERE hash='" + hash_of_exe + "'";
        rc = sqlite3_exec(db, const_cast<char*>(sql.c_str()), callback, (void*)&data, &err_msg);
        
        if (!data) {
            return false;
        }
    }
    else if (action == "ADD") {
        sql = "INSERT INTO viruses (name, hash) VALUES ('addedByUser', '" + hash_of_exe + "');";
        rc = sqlite3_exec(db, const_cast<char*>(sql.c_str()), callback, 0, &err_msg);
    }
    else if (action == "DELETE") {
        sql = "DELETE FROM viruses WHERE hash='" + hash_of_exe + "'";
        rc = sqlite3_exec(db, const_cast<char*>(sql.c_str()), callback, 0, &err_msg);
    }
    else {
        std::cout << "ERROR OF COMMAND" << std::endl;
    }

    if (rc != SQLITE_OK) {
        sqlite3_free(err_msg);
    }

    sqlite3_close(db);

    return true;
}


//int main(int argc, char** argv) {
//    database_control("123", "ADD");
//    std::cout << database_control("123", "FIND") << std::endl;
//    database_control("123", "DELETE");
//    std::cout << database_control("123", "FIND") << std::endl;
//    database_control("123", "DELETE");
//    std::cout << database_control("123", "FIND") << std::endl;
//    database_control("123", "ADD");
//    std::cout << database_control("123", "FIND") << std::endl;
//    database_control("123", "ADD");
//    database_control("124", "ADD");
//    database_control("1224", "ADD");
//    database_control("112324", "ADD");
//    database_control("1214", "ADD");
//
//
//    return 0;
//}
