#include "bypass.h"

std::vector<std::string> infoAboutPath(std::string path)
{ 
    fs::path pathObj{path};
    std::vector<std::string> result;

    result.push_back(pathObj.root_name().string());
    result.push_back(pathObj.root_path().string());
    result.push_back(pathObj.relative_path().string());
    result.push_back(pathObj.filename().string());
    result.push_back(pathObj.stem().string());
    result.push_back(pathObj.extension().string());

    return result;
}

std::vector<std::string> bypassDirectory(std::string path_string)
{
    fs::path pathdir{path_string};
    fs::recursive_directory_iterator iterDir{pathdir};
    std::vector<std::string> result_base_path;

    for (auto iterElementDir : iterDir)
    {
        if (infoAboutPath(iterElementDir.path().string()).back() == ".exe")
        {
            result_base_path.push_back(iterElementDir.path().string());
        }
    }

    return result_base_path;
}
