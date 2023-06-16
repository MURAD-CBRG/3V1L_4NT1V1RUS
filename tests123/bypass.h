#ifndef BYPASS_H
#define BYPASS_H

#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#include <iostream>
#include <filesystem>
#include <vector>
#include <string>

namespace fs = std::filesystem;

/**
 * \brief Returns information about the specified file path.
 * \return A vector of strings containing information about the file.
 * 
 * This function takes a file path as a string and returns information about the file.
 * The information includes the root name, root path, relative path, filename, stem, and extension of the file.
 */
std::vector<std::string> infoAboutPath(std::string path);

/**
 * \brief Recursively searches a directory for executable files.
 * \return A vector of strings containing the paths of all executable files found in the directory and its subdirectories.
 *
 * This function takes a directory path as a string and returns the paths of all executable files 
 * found in the directory and its subdirectories. It uses the infoAboutPath() function to check
 * whether each file has a ".exe" extension.
 */
std::vector<std::string> bypassDirectory(std::string path_string);

#endif // BYPASS_H
