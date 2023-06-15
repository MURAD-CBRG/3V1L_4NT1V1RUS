#ifndef TEST_H
#define TEST_H

#include <iostream>
#include <string>
#include "sqllite/sqlite3.h"

static int callback(void* NotUsed, int argc, char** argv, char** azColName);
bool search_by_signature(std::string virus_hash);
int abc();

#endif // TEST_H
