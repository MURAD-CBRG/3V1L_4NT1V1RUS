#include <iostream>
#include <fstream>
#include <memory>
#include <cmath>
#include <filesystem>
#include <string>
#include <cstring>
#include <algorithm>
#include "sha256/sha256.h"
#include <vector>

using std::cout;

inline int char_to_decimal(char chr){
    int dec = chr;
    if(dec < 0)
        dec += 256;
    return dec;
}



class Signature
{
public:
    Signature(std::string filename) {
        this->filename = filename;
        file.open(this->filename, std::ios::in | std::ios::binary);
        this->read_MS_DOS_HEADER();
        this->read_PE_HEADER();
    }

    ~Signature() {
        this->file.close();
        MS_DOS_HEADER_BUFFER.clear();
        PE_HEADER_BUFFER.clear();
    }


    void read_MS_DOS_HEADER() { // init vector[64] of unsigned chars
        MS_DOS_HEADER_BUFFER = std::vector<unsigned char>(64);
        file.seekg(0, std::ios::beg);

        if(!file.read(reinterpret_cast<char*>(MS_DOS_HEADER_BUFFER.data()), 64))
            throw std::invalid_argument{"Can't read the file!"};

        if(MS_DOS_HEADER_BUFFER[0] != 0x4d || MS_DOS_HEADER_BUFFER[1] != 0x5a)
            throw std::invalid_argument{"The file is not EXE!"};
    }



    int get_PE_offset(){ // returns the position of PE header in file
        int offset = 0;

        for(int i = 60; i < 64; i++)
            offset += pow(256, i - 60) * MS_DOS_HEADER_BUFFER[i]; // size is 64 of MS DOS Header

        std::cout<<"The PE_offset is "<<offset<<std::endl;

        return offset;
    }



    void read_PE_HEADER() { // 24 bytes 4 - signature, 20 - other info
        int offset = get_PE_offset();
        file.seekg(offset, std::ios::beg);

        PE_HEADER_BUFFER = std::vector<unsigned char>(24);
        if(!file.read(reinterpret_cast<char*>(PE_HEADER_BUFFER.data()), 24))
            throw std::invalid_argument{"Can't read the file!"};

        cout<<"PE IS: \n";

        int iter = 0;
        while (iter < 24) {
            cout<<(int)PE_HEADER_BUFFER[iter]<<" ";
            iter++;
        }
        cout<<"\nPE END \n";

        if(PE_HEADER_BUFFER[0] != 0x50 || PE_HEADER_BUFFER[1] != 0x45 || PE_HEADER_BUFFER[2] != 0 || PE_HEADER_BUFFER[3] != 0)
            throw std::invalid_argument{"Can't read the PE header! Probably it is missing."};
    }



    int getSections_offset(){
        int offset = get_PE_offset() + 24; // offset of Optional Header
        // 21 and 22 - bytes of optional header size
        offset += PE_HEADER_BUFFER[20] + PE_HEADER_BUFFER[21] * 256;
        std::cout<<"the size of optional header: "<<(int)PE_HEADER_BUFFER[20]<<" "<<(int)PE_HEADER_BUFFER[21]<<std::endl;
        return offset;
    }


    int get_number_of_sections(){
        // 7 and 8 - bytes that define the nubmer of sections
        return PE_HEADER_BUFFER[6] + PE_HEADER_BUFFER[7] * 256;
    }


    void print(unsigned cnt, int pos=-1){
        if(pos > 0)
            file.seekg(pos, std::ios::beg);
        cout<<"START print in "<<pos<<" "<<cnt<<std::endl;

        char * buffer = new char[cnt];
        unsigned char * bytes_buffer = new unsigned char[cnt];
        if(!file.readsome(buffer, cnt))
            throw std::invalid_argument{"Can't read the file!"};
        std::transform(buffer, buffer + cnt, bytes_buffer, [](char c){return static_cast<unsigned char>(c);});
        for(int i = 0; i < cnt; i++)
            std::cout<<(int)bytes_buffer[i]<<' ';
        cout<<"\nEND of print\n";
    }



    int sum_up_bytes(unsigned short size, int pos=-1){
        if(size > 4)
            throw std::invalid_argument{"Can't sum up so many bytes!"};

        if(pos > 0)
            file.seekg(pos, std::ios::beg);

        int res = 0;
        for(int i = 0; i < 4; i++){
            char byte;
            if(!file.get(byte))
                throw std::invalid_argument{"Can't read the file!"};
            res += static_cast<unsigned char>(byte) * pow(256, i);
        }

        return res;
    }



    void get_hash(){
        int start = getSections_offset();
        file.seekg(start, std::ios::beg);
        std::string target = ".text\0\0";

        int size = get_number_of_sections();
        for(int i = 0; i < size; i++){
            std::vector<char> name(8);
            file.read(name.data(), 8);
            if(target.compare(name.data()) == 0){
                file.seekg(start + i * 40 + 16, std::ios::beg);
                int size_of_raw_data = sum_up_bytes(4);
                int offset_of_raw_data = sum_up_bytes(4);

                std::vector<char> raw_data(size_of_raw_data);
                file.seekg(offset_of_raw_data, std::ios::beg);
                file.read(reinterpret_cast<char*>(raw_data.data()), size_of_raw_data);
                std::string str(raw_data.begin(), raw_data.end());
                std::string sha = sha256(str);
                std::cout<<sha<<std::endl;
                
            }
            file.seekg(start + (i + 1) * 40, std::ios::beg); // moving to the next section
        }
    }



private:

    std::string filename;
    std::ifstream file;
    std::vector<unsigned char> MS_DOS_HEADER_BUFFER;
    std::vector<unsigned char> PE_HEADER_BUFFER;
};





int main(int argc, char** argv) {

    std::cout<<"START OF SCAN\n";

    std::string name;
    std::cin>>name;
    Signature sig2(name);

    int x = sig2.getSections_offset();
    std::cout<<"The offset is "<<x<<std::endl;
    sig2.print(x, 100);
    sig2.get_hash();

    std::cout << std::endl << "END OF SCAN" << std::endl;


    return 0;
}