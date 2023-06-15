#include "stdio.h"
#include "stdlib.h"
#include "sqllite/sqlite3.h"
#include <string>
#include <iostream>


static int callback(void* NotUsed, int argc, char** argv, char** azColName) {
    int i;

    for (i = 0; i < argc; i++) {
        std::cout << argv[i] << std::endl;
    }
    
    std::cout << "\n" << std::endl;
    
    return 0;
}




bool search_by_signature(std::string virus_hash) {
   sqlite3 *db;
   int rc;  // commander of database
   char* error_msg = 0;
   std::string sql;
   const char* data = "Callback function called";
   bool flag{ true };

   /* Open database */
   rc = sqlite3_open("virus_test_database.db", &db);
   
   if( rc ) {
        std::cout << "not opened" << std::endl;
        return false;
   } else {
        std::cout << "opened" << std::endl;
   }

   sql = "SELECT * FROM viruses WHERE hash='" + virus_hash + "'";

   rc = sqlite3_exec(db, const_cast<char*>(sql.c_str()), callback, (void*)data, &error_msg);
   
   if( rc != SQLITE_OK ) {
        std::cout << "not ok" << std::endl;
        
        sqlite3_free(error_msg);
        sqlite3_close(db);

        return false;

   } else {
        std::cout << "ok" << std::endl;
   }

   sqlite3_close(db);
   return true;
}


int main(int argc, char** argv) {
    if (search_by_signature("123")) {
        std::cout << "exists" << std::endl;
    } else {
        std::cout << "not exists" << std::endl;
    }

    return 0;
}
