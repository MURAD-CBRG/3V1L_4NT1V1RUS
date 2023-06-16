#ifndef DIR_READER_H
#define DIR_READER_H

#include <QTextEdit>
#include <QString>
#include <string>
#include "db_manager/database_api.h"
#include "signature.h"
#include "bypass.h"

void read_dir(std::string dir, QTextEdit* redactor);

#endif // DIR_READER_H
