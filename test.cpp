#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <string>
#include <iostream>
#include <vector>

#include "bypass.h"
#include "conf.h"
#include "database_api.h"
#include "signature.h"

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

TEST_CASE("bypassDirectory throws error for non-existing directory") {  // ok
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

TEST_SUITE("Signature"){
    TEST_CASE("Right reading of MS_DOS header"){
        Signature sig{"labtest4/sample_virus.exe"};
        unsigned char ucDataBlock[64] = {
            0x4D, 0x5A, 0x90, 0x00, 0x03, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00,
            0xFF, 0xFF, 0x00, 0x00, 0xB8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
            0x80, 0x00, 0x00, 0x00
        };
        std::vector<unsigned char> ms_dos = sig.get_MS_DOS_HEADER_BUFFER();
        for(int i = 0; i < ms_dos.size(); i++){
            REQUIRE(i < 64);
            CHECK(ucDataBlock[i] == ms_dos[i]);
        }
    }

    TEST_CASE("Right reading of PE header"){
        Signature sig{"labtest4/sample_virus.exe"};
        unsigned char ucDataBlock[24] = {
            0x50, 0x45, 0x00, 0x00, 0x64, 0x86, 0x11, 0x00, 0x69, 0xED, 0x8C, 0x64,
            0x00, 0x72, 0x00, 0x00, 0x37, 0x05, 0x00, 0x00, 0xF0, 0x00, 0x26, 0x00
        };
        std::vector<unsigned char> pe = sig.get_PE_HEADER_BUFFER();
        for(int i = 0; i < pe.size(); i++){
            REQUIRE(i < 24);
            CHECK(ucDataBlock[i] == pe[i]);
        }
    }

    TEST_CASE("Opening non-existing file"){
        CHECK_THROWS_AS(Signature("labtest4/sample_virus_non_existing.exe"), std::ifstream::failure);
    }

    TEST_CASE("Opening not exe file"){
        CHECK_THROWS_AS(Signature("labtest4/not.exe"), std::invalid_argument);
    }

    TEST_CASE("PE offset is correct"){
        Signature sig{"labtest4/sample_virus.exe"};
        CHECK(sig.get_PE_offset() == 128);
    }

    TEST_CASE("Sections offset is correct"){
        Signature sig{"labtest4/sample_virus.exe"};
        CHECK(sig.get_Sections_offset() == 392);
    }

    TEST_CASE("Number_of_sections is correct"){
        Signature sig{"labtest4/sample_virus.exe"};
        CHECK(sig.get_number_of_sections() == 17);
    }

    TEST_CASE("Right Suming Up of bytes"){
        Signature sig{"labtest4/sample_virus.exe"};
        CHECK_THROWS_AS(sig.sum_up_bytes(-3, 0), std::invalid_argument);
        CHECK(sig.sum_up_bytes(3, 0) == 131595);
        CHECK(sig.sum_up_bytes(1, 0) == 40);
        CHECK(sig.sum_up_bytes(4, 64) == 247078670);
        CHECK(sig.sum_up_bytes(2, 64) == 7950);
        CHECK(sig.sum_up_bytes(2, -3) == 3770);
    }

    TEST_CASE("Right hash of file"){
        std::string right_hash = "50facf88c7b8e1d6f324ea3462c322009e02bdbd82f8b2c79f0fb13a85b415e0";
        Signature sig{"labtest4/sample_virus.exe"};
        CHECK(sig.get_hash() == right_hash);
    }
}


TEST_SUITE("Database"){
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
        REQUIRE(result_delete_nonexisting);
        REQUIRE_FALSE(result_find_deleted);
    }
}
