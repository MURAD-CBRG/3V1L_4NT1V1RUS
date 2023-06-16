#include "analizerseparated.h"

analizerSeparated::analizerSeparated(QString name,
                                     int interval_seconds,
                                     std::vector<std::string> dirs,
                                     QTextEdit* redactor) :
    name(name),
    interval_seconds(interval_seconds),
    dirs(dirs),
    redactor(redactor) {}

void analizerSeparated::analize_for_intervals(){
    while(true){
        for(std::string s: dirs){
            read_dir(s, redactor);
            if (QThread::currentThread()->isInterruptionRequested())
                return;
        }
        QThread::msleep(1000 * interval_seconds);
    }
}
