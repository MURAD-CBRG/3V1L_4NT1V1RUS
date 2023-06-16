#ifndef BYPASS_H
#define BYPASS_H

#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#include <iostream>
#include <filesystem>
#include <vector>
#include <string>

namespace fs = std::filesystem;

std::vector<std::string> infoAboutPath(std::string path);
std::vector<std::string> bypassDirectory(std::string path_string);

#endif // BYPASS_H
