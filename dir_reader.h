#ifndef DIR_READER_H
#define DIR_READER_H

#include <QTextEdit>
#include <QString>
#include <string>
#include "database_api.h"
#include "signature.h"
#include "bypass.h"

/**
 * \brief Reads the files in the specified directory, computes their SHA256 hash using the Signature class, and writes a message to a QTextEdit widget indicating whether each file is a virus or not.
 *
 * \param dir The path to the directory to read.
 * \param redactor A pointer to a QTextEdit widget where log messages will be written.
 *
 * \throws std::ifstream::failure If a file in the directory cannot be read.
 * \throws std::invalid_argument If a file in the directory is not an executable file.
 * \throws std::filesystem::__cxx11::filesystem_error If the directory does not exist.
 */
void read_dir(std::string dir, QTextEdit* redactor);

#endif // DIR_READER_H
