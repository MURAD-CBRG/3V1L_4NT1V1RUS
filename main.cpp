#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING

#include <iostream>
#include <experimental/filesystem>
#include <vector>
#include <string>

namespace fs = std::experimental::filesystem;


std::vector<std::string> infoAboutPath(std::string path);
std::vector<std::string> bypassDirectory(std::string path_string);


int main(int argc, char** argv)
{
	for (auto i : infoAboutPath("test_file.txt")) std::cout << i << std::endl;
	for (auto i : bypassDirectory("C:/Users/CYBORG/Desktop/secret_project")) std::cout << i << std::endl;

	return 0;
}


std::vector<std::string> infoAboutPath(std::string path) {  // Принимает путь до файла и выводит информацию о нем
	fs::path pathObj{ path };
	std::vector<std::string> result;

	result.push_back(pathObj.root_name().string());
	result.push_back(pathObj.root_path().string());
	result.push_back(pathObj.relative_path().string());
	result.push_back(pathObj.filename().string());
	result.push_back(pathObj.stem().string());
	result.push_back(pathObj.extension().string());

	return result;
}


std::vector<std::string> bypassDirectory(std::string path_string) {  // Принимает путь до каталога и рекурсивно выводит все файлы и каталоги, находящиеся в нем
	fs::path pathdir{ path_string };
	fs::recursive_directory_iterator iterDir{ pathdir };
	std::vector<std::string> result_base_path;

	for (auto iterElementDir : iterDir) {
		result_base_path.push_back(iterElementDir.path().string());
	}

	return result_base_path;
}
