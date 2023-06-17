#include "conf.h"

ConfigurationAnalyse getConfigurationForAnalysis()
{
    std::ifstream file("conf_analyse.conf");
    if (!file.is_open())
        throw std::fstream::failure{"No config file!"};

    ConfigurationAnalyse conf;

    std::string str;
    int cur_iter{0};
    while (std::getline(file, str))
    {
        if (cur_iter == 0)
        {
            conf.work_flag = atoi(str.c_str());
        }
        else if (cur_iter == 1)
        {
            conf.time_interval = atoi(str.c_str());
        }
        else
        {
            conf.baseDirs.push_back(str);
        }

        cur_iter++;
    }

    return conf;
}

void setConfigurationAnalysis(ConfigurationAnalyse conf)
{
    std::ofstream file("conf_analyse.conf");
    if (!file.is_open())
        throw std::ofstream::failure{"Can't create config!"};

    file << std::to_string(static_cast<int>(conf.work_flag)) << std::endl;
    file << std::to_string(static_cast<int>(conf.time_interval)) << std::endl;

    for (std::string curPath : conf.baseDirs)
    {
        file << curPath << std::endl;
    }
    file.close();
}
