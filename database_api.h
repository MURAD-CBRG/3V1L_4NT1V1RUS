#ifndef DATABASE_API_H
#define DATABASE_API_H

#include <string>

#include "sqllite/sqlite3.h"

/**
 * \brief A callback function used to process the results of a SQLite3 query.
 * \param NotUsed A pointer to user-defined data passed to the query execution function.
 * \param argc The number of columns in the result set.
 * \param argv An array of pointers to strings containing the values for each column in the result set.
 * \param azColName An array of pointers to strings containing the names of each column in the result set.
 * \return Always returns 0.
 *
 * This function is used as a callback for the `sqlite3_exec` function to process the results of a
 * SQLite3 query. It sets a boolean flag to true when called.
 */
static int callback(void *NotUsed, int argc, char **argv, char **azColName);

/**
 * \brief Interacts with a SQLite3 database to perform common operations.
 * \param hash_of_exe The hash of an executable file.
 * \param action The action to perform on the database ("FIND", "ADD", or "DELETE").
 * \return True if the action is completed successfully, false otherwise.
 *
 * This function performs one of three actions:
 * - "FIND": executes a SQL query to select all rows from the `viruses` table in the database
 *   with `hash_of_exe`. If no matching row is found, the function returns false.
 * - "ADD": executes an SQL query to insert a new row into the `viruses` table with a `name`
 *   value of "addedByUser" and a `hash` value of the input `hash_of_exe` string.
 * - "DELETE": executes an SQL query to delete all rows from the `viruses` table where the `hash`
 *   column matches the input `hash_of_exe` string.
 */
bool database_control(std::string hash_of_exe, std::string action);

#endif
