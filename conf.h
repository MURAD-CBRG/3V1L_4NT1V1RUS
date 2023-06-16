#ifndef CONF_H
#define CONF_H

#include <fstream>
#include <string>
#include <vector>
#include <iostream>


struct ConfigurationAnalyse {
    bool work_flag;
    int time_interval;
    std::vector<std::string> baseDirs;
};


ConfigurationAnalyse getConfigurationForAnalysis();
void setConfigurationAnalysis(ConfigurationAnalyse conf);

#endif
