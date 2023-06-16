#ifndef ANALIZERSEPARATED_H
#define ANALIZERSEPARATED_H

#include <QObject>
#include <QThread>
#include <iostream>
#include <vector>
#include <string>

class analizerSeparated : public QObject  // EXAMPLE OF THREAD
{
public:
    explicit analizerSeparated(QString threadName, int interval_in_seconds, std::vector<std::string> dirs);
    void do_something();

private:
    QString name;  // NAME OF THREAD - NOT NECESSERY
    int interval_seconds;
    std::vector<std::string> dirs;
};


#endif // ANALIZERSEPARATED_H
