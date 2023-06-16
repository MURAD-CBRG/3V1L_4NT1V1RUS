#include <fstream>
#include <string>
#include <vector>
#include <iostream>


struct ConfigurationAnalyse {
    bool work_flag;
    int time_interval;
    int dirs_amount;
    std::vector<std::string> baseDirs;
};


ConfigurationAnalyse getConfigurationForAnalysis()
{
    std::ifstream file("conf_analyse.conf");
    std::string str;
    int cur_iter{ 0 };
    std::vector<std::string> base;

    ConfigurationAnalyse conf;


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


//int main(int argc, char** argv) {
//    ConfigurationAnalyse conf = getConfigurationForAnalysis();
//
//    std::cout << conf.work_flag << std::endl;
//    std::cout << conf.time_interval << std::endl;
//    std::cout << conf.dirs_amount << std::endl;
//
//    for (std::string curDir : conf.baseDirs) {
//        std::cout << curDir << std::endl;
//    }
//
//    return 0;
//}