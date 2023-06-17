#ifndef CONF_H
#define CONF_H

#include <fstream>
#include <string>
#include <vector>
#include <iostream>

/**
 * \brief The configuration for automatic analysis.
 */
struct ConfigurationAnalyse
{
    bool work_flag;                    /**< Indicator if automatic analysis is enabled or not. */
    int time_interval;                 /**< The time interval between automatic analyses in seconds. */
    std::vector<std::string> baseDirs; /**< A vector of strings representing the directories to be included in the automatic analysis. */
};

/**
 * \brief Reads the configuration for automatic analysis from a file.
 * \return The configuration for automatic analysis.
 *
 * This function reads the configuration for automatic analysis from a file called "conf_analyse.conf".
 * If the file exists, it reads the configuration from the file and
 * returns a ConfigurationAnalyse struct with the values read from the file.
 */
ConfigurationAnalyse getConfigurationForAnalysis();

/**
 * \brief Writes the configuration for automatic analysis to a file.
 * \param conf The configuration for automatic analysis.
 *
 * This function takes a ConfigurationAnalyse struct as an argument and writes the values
 * to a file called "conf_analyse.conf".
 */
void setConfigurationAnalysis(ConfigurationAnalyse conf);

#endif
