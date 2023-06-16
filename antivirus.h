#ifndef ANTIVIRUS_H
#define ANTIVIRUS_H

#include <iostream>
#include <fstream>
#include <cmath>
#include <filesystem>
#include <string>
#include <cstring>
#include <algorithm>
#include <vector>

class Signature
{
public:
    Signature(std::string filename);
    ~Signature();
    int get_PE_offset();
    int get_Sections_offset();
    int get_number_of_sections();
    void print(unsigned cnt, int pos);
    int sum_up_bytes(unsigned short size, int pos);
    std::string get_hash();
private:

    void read_MS_DOS_HEADER();

    void read_PE_HEADER();

    std::string filename;
    std::ifstream file;
    std::vector<unsigned char> MS_DOS_HEADER_BUFFER;
    std::vector<unsigned char> PE_HEADER_BUFFER;
};

#endif
