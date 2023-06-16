#ifndef ANALIZERSEPARATED_H
#define ANALIZERSEPARATED_H

#include <QObject>
#include <QThread>
#include <QTextEdit>
#include <QMessageBox>
#include <iostream>
#include <vector>
#include <string>

#include "dir_reader.h"

class analizerSeparated : public QObject  // EXAMPLE OF THREAD
{
public:
    explicit analizerSeparated(int interval_in_seconds,
                               std::vector<std::string> dirs,
                               QTextEdit* redactor);
    void analize_for_intervals();

private:
    int interval_seconds;
    std::vector<std::string> dirs;
    QTextEdit* redactor;
};


#endif // ANALIZERSEPARATED_H
