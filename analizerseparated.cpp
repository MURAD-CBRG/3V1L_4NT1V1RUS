#include "analizerseparated.h"

analizerSeparated::analizerSeparated(QString name, int interval_seconds, std::vector<std::string> dirs) :
    name(name),
    interval_seconds(interval_seconds),
    dirs(dirs) {}

void analizerSeparated::do_something(){
    while(true){
        for(auto s: dirs){
            std::cout<<s<<std::endl;
            if (QThread::currentThread()->isInterruptionRequested())
                return;
        }
        QThread::msleep(1000 * interval_seconds);
    }
}
