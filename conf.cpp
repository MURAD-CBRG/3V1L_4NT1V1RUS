#include "conf.h"

ConfigurationAnalyse getConfigurationForAnalysis()
{
    std::ifstream file("conf_analyse.conf");
    if(!file.is_open())
        throw std::fstream::failure{"No config file!"};
    
    ConfigurationAnalyse conf;

    std::string str;
    int cur_iter{ 0 };
    while (std::getline(file, str))
    {
        if (cur_iter == 0) {
            conf.work_flag = atoi(str.c_str());
        }
        else if (cur_iter == 1) {
            conf.time_interval = atoi(str.c_str());
        }
        else {
            conf.baseDirs.push_back(str);
        }

        cur_iter++;
    }

    return conf;
}