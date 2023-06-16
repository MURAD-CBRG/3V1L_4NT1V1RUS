#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <string>
#include <iostream>
#include <vector>

#include "bypass.h"
#include "conf.h"

#include "doctest.h"


// INFO_ABOUT_PATH
TEST_CASE("infoAboutPath returns correct information for Windows absolute path with filename and extension") { // ok
    std::vector<std::string> result = infoAboutPath("labtest/a.exe");

    REQUIRE(result.size() == 6);
    CHECK(result[0] == "");
    CHECK(result[1] == "");
    CHECK(result[2] == "labtest/a.exe");
    CHECK(result[3] == "a.exe");
    CHECK(result[4] == "a");
    CHECK(result[5] == ".exe");
}

TEST_CASE("infoAboutPath returns correct information for Windows relative path with filename and extension") {  // ok
    std::vector<std::string> result = infoAboutPath("labtest/a.txt");
    REQUIRE(result.size() == 6);
    CHECK(result[0] == "");
    CHECK(result[1] == "");
    CHECK(result[2] == "labtest/a.txt");
    CHECK(result[3] == "a.txt");
    CHECK(result[4] == "a");
    CHECK(result[5] == ".txt");
}


// BYPASS
TEST_CASE("bypassDirectory returns correct paths for existing directory with .exe files") {  // ok 
    std::vector<std::string> result = bypassDirectory("labtest2");
    
    REQUIRE(result.size() == 2);
    CHECK(result[0].replace(result[0].find("\\"), 1, "/") == "labtest2/simple1.exe");
    CHECK(result[1].replace(result[1].find("\\"), 1, "/").replace(result[1].find("\\"), 1, "/") == "labtest2/subdirectory/simple2.exe");
}

TEST_CASE("bypassDirectory returns empty vector for non-existing directory") {  // ok
    //std::vector<std::string> result = bypassDirectory("test_directory/subdirectory");
    CHECK_THROWS(bypassDirectory("test_directory/subdirectory"));
}

TEST_CASE("bypassDirectory returns empty vector for directory with no .exe files") {  // ok
    std::vector<std::string> result = bypassDirectory("empty");
    REQUIRE(result.size() == 0);
}


// CONFIGURATION ANALYSE
TEST_CASE("getConfigurationForAnalyse returns correct configuration for valid config file") {  // ok
    std::ofstream temp_file("conf_analyse.conf");
    temp_file << "1\n1000\nC:/test_dir\nD:/another_test_dir\n";
    temp_file.close();

    ConfigurationAnalyse result = getConfigurationForAnalysis();
    REQUIRE(result.work_flag == 1);
    REQUIRE(result.time_interval == 1000);
    REQUIRE(result.baseDirs.size() == 2);
    CHECK(result.baseDirs[0] == "C:/test_dir");
    CHECK(result.baseDirs[1] == "D:/another_test_dir");

    std::remove("conf_analyse.conf");
}



TEST_CASE("setConfigurationAnalysis writes valid configuration to file") {
    ConfigurationAnalyse conf;
    conf.work_flag = 1;
    conf.time_interval = 30;
    conf.baseDirs = {"dir1", "dir2"};

    setConfigurationAnalysis(conf);

    std::ifstream file("conf_analyse.conf");
    REQUIRE(file.is_open());

    std::string line;
    std::getline(file, line);
    REQUIRE(line == "1");

    std::getline(file, line);
    REQUIRE(line == "30");

    std::getline(file, line);
    REQUIRE(line == "dir1");

    std::getline(file, line);
    REQUIRE(line == "dir2");
}





TEST_CASE("database_control performs FIND action correctly with empty database") {
    std::string hash = "666";

    bool result = database_control(hash, "FIND");

    REQUIRE_FALSE(result);
}


TEST_CASE("database_control performs ADD and FIND actions correctly") {
    std::string hash = "666_new";

    bool result_add = database_control(hash, "ADD");
    bool result_find_existing = database_control(hash, "FIND");
    bool result_find_nonexisting = database_control("nonexistent_hash", "FIND");

    REQUIRE(result_add);
    REQUIRE(result_find_existing);
    REQUIRE_FALSE(result_find_nonexisting);
}


TEST_CASE("database_control performs DELETE and FIND actions correctly") {
    std::string hash = "666";

    bool result_add = database_control(hash, "ADD");
    bool result_delete_existing = database_control(hash, "DELETE");
    bool result_delete_nonexisting = database_control("IAMSHADOW", "DELETE");
    bool result_find_deleted = database_control(hash, "FIND");

    REQUIRE(result_add);
    REQUIRE(result_delete_existing);
    REQUIRE_FALSE(result_delete_nonexisting);
    REQUIRE_FALSE(result_find_deleted);
}

