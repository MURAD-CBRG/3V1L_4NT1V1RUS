#ifndef DATABASE_API_H
#define DATABASE_API_H

#include <string>

#include "sqllite/sqlite3.h"

static int callback(void* NotUsed, int argc, char** argv, char** azColName);
bool database_control(std::string hash_of_exe, std::string action);

#endif
