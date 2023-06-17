#include "database_api.h"

static int callback(void *NotUsed, int argc, char **argv, char **azColName)
{
    (*(bool *)NotUsed) = true;

    return 0;
}

bool database_control(std::string hash_of_exe, std::string action)
{
    sqlite3 *db;
    char *err_msg = 0;
    int rc{sqlite3_open("virus_test_database.db", &db)};
    std::string sql;

    if (rc)
    {
        return false;
    }

    if (action == "FIND")
    {
        bool data = false;
        sql = "SELECT * FROM viruses WHERE hash='" + hash_of_exe + "'";
        rc = sqlite3_exec(db, const_cast<char *>(sql.c_str()), callback, (void *)&data, &err_msg);

        if (!data)
        {
            return false;
        }
    }
    else if (action == "ADD")
    {
        sql = "INSERT INTO viruses (name, hash) VALUES ('addedByUser', '" + hash_of_exe + "');";
        rc = sqlite3_exec(db, const_cast<char *>(sql.c_str()), callback, 0, &err_msg);
    }
    else if (action == "DELETE")
    {
        sql = "DELETE FROM viruses WHERE hash='" + hash_of_exe + "'";
        rc = sqlite3_exec(db, const_cast<char *>(sql.c_str()), callback, 0, &err_msg);
    }

    if (rc != SQLITE_OK)
    {
        sqlite3_free(err_msg);
    }

    sqlite3_close(db);

    return true;
}
