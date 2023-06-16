#ifndef DIR_READER_H
#define DIR_READER_H

#include <QTextEdit>
#include <QString>
#include <string>
#include "db_manager/database_api.h"
#include "signature.h"
#include "bypass.h"

/**
 * \brief Reads a directory and its subdirectories and checks the files for virus signatures.
 * \param dir The path of the directory to be read.
 * \param redactor A pointer to a QTextEdit widget where the results of the scan will be displayed.
 *
 * This function takes a directory path and a QTextEdit widget as input. It reads the directory and its subdirectories,
 * and checks each file for malware signatures. If a signature is found, it is displayed in the QTextEdit widget.
 */
void read_dir(std::string dir, QTextEdit* redactor);

#endif // DIR_READER_H
