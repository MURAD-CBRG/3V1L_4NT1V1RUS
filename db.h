#ifndef DB_H
#define DB_H

#include "stdlib.h"
#include "sqllite/sqlite3.h"
#include <string>
#include <iostream>

static int callback(void* NotUsed, int argc, char** argv, char** azColName);
bool search_by_signature(std::string virus_hash);

#endif // DB_H
