#include <iostream>
#include <fstream>
#include <memory>
#include <cmath>
#include <filesystem>
#include <string>
#include <cstring>
#include <algorithm>
#include "cryptopp/sha.h"

using std::cout;
using CryptoPP::byte;

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
        file1.open(this->filename, std::ios::in | std::ios::binary);
        this->read_MS_DOS_HEADER();
        this->read_PE_HEADER();
    }

    ~Signature() {
        this->file1.close();

        delete[] MS_DOS_HEADER_BUFFER;
        delete[] PE_HEADER_BUFFER;
        delete[] SIGNATURE_ANALYSIS;
    }

    void read_MS_DOS_HEADER() { // returns int[64] with decimal values of file bytes
        file1.seekg(0, std::ios::beg);
        //cout<<"\nDOS HEADER\n";
        char * buffer = new char[64];
        if(!file1.readsome(buffer, 64))
            throw std::invalid_argument{"Can't read the file!"};
        std::transform(buffer, buffer + 64, MS_DOS_HEADER_BUFFER, 
                        [](char c){ return static_cast<unsigned char>(c); });
        delete[] buffer;
        /*while (iter < 64) {
            if(!file1.get(current_byte))
                
            //cout<<current_byte<<" ";
            MS_DOS_HEADER_BUFFER[iter] = char_to_decimal(current_byte);
            iter++;
        }*/
        if(MS_DOS_HEADER_BUFFER[0] != 0x4d || MS_DOS_HEADER_BUFFER[1] != 0x5a)
            throw std::invalid_argument{"The file is not EXE!"};
        //cout<<"END OF DOS\n";
    }

    int get_PE_offset(){
        //cout<<"\nREADING PE_offset\n"; 
        int offset = 0;
        for(int i = 60; i < 64; i++){
            offset += pow(256, i - 60) * MS_DOS_HEADER_BUFFER[i]; // size is 64
        }
        std::cout<<"The PE_offset is "<<offset<<std::endl;
        //cout<<"END of PE_offset\n";
        return offset;
    }

    void read_PE_HEADER() { // 24 bytes 4 - signature, 20 - other info
        int offset = get_PE_offset();
        file1.seekg(offset, std::ios::beg);

        char * buffer = new char[24];
        if(!file1.readsome(buffer, 24))
            throw std::invalid_argument{"Can't read the file!"};
        std::transform(buffer, buffer + 24, PE_HEADER_BUFFER,
                        [](char c){ return static_cast<unsigned char>(c); });
        delete[] buffer;
        
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
            file1.seekg(pos, std::ios::beg);
        cout<<"START print in "<<pos<<" "<<cnt<<std::endl;
        char * buffer = new char[cnt];
        unsigned char * bytes_buffer = new unsigned char[cnt];
        if(!file1.readsome(buffer, cnt))
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
            file1.seekg(pos, std::ios::beg);
        int res = 0;
        for(int i = 0; i < 4; i++){
            char byte;
            if(!file1.get(byte))
                throw std::invalid_argument{"Can't read the file!"};
            res += static_cast<unsigned char>(byte) * pow(256, i);
        }
        return res;
    }

    void get_hash(){
        int start = getSections_offset();
        file1.seekg(start, std::ios::beg);

        int size = get_number_of_sections();
        for(int i = 0; i < size; i++){
            char* name = new char[8];
            file1.readsome(name, 8);
            if(strcmp(name, ".text\0\0") == 0){
                file1.seekg(start + i * 40 + 16, std::ios::beg);
                int size_of_raw_data = sum_up_bytes(4);
                int offset_of_raw_data = sum_up_bytes(4);
                std::cout<<size_of_raw_data<<" "<<offset_of_raw_data<<std::endl;
            }
            file1.seekg(start + (i + 1) * 40, std::ios::beg); // moving to the next section
        }
    }

private:
    int pe_cur{0};

    std::string filename;
    std::ifstream file1;
    unsigned char* MS_DOS_HEADER_BUFFER = new unsigned char[64];
    unsigned char* PE_HEADER_BUFFER = new unsigned char[24];
    unsigned char* SIGNATURE_ANALYSIS = new unsigned char[300];
};


int main(int argc, char** argv) {

    std::string input = "Hello, world!";
    CryptoPP::SHA256 hash;
    byte digest[CryptoPP::SHA256::DIGESTSIZE];
    hash.CalculateDigest(digest, (const byte*)input.c_str(), input.length());
    std::cout << "SHA-256 hash of \"" << input << "\": ";
    for(int i = 0; i < CryptoPP::SHA256::DIGESTSIZE; i++) {
        printf("%02x", digest[i]);
    }
    std::cout << std::endl;

    std::cout << "START" << std::endl;


    // Signature sig1("gamemd.exe");
    // int x = sig1.get_PE_offset();
    // sig1.print(x, 2);
    // int* pe = sig1.read_PE_HEADER();
    // cout<<pe[6]<<" "<<pe[7];
    std::string name;
    std::cin>>name;
    Signature sig2(name);
    //int x = sig2.get_PE_offset();
    int x = sig2.getSections_offset();
    //std::cout<<<<x
    std::cout<<"The offset is "<<x<<std::endl;
    sig2.print(x, 100);
    sig2.get_hash();

    std::cout << std::endl << "END OF SCAN" << std::endl;


    return 0;
}