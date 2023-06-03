#include <iostream>
#include <fstream>
#include <memory>
#include <cmath>
#include <filesystem>

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
        file1.open(this->filename, std::ios::in | std::ios::binary);
    }

    ~Signature() {
        this->file1.close();

        delete[] MS_DOS_HEADER_BUFFER;
        delete[] PE_HEADER_BUFFER;
        delete[] SIGNATURE_ANALYSIS;
    }

    int* getMS_DOS_HEADER() { // returns int[64] with decimal values of file bytes
        file1.seekg(0, std::ios::beg);
        char current_byte;
        int iter{0};
        //cout<<"\nDOS HEADER\n";
        while (iter < 64) {
            if(!file1.get(current_byte))
                throw std::invalid_argument{"Can't read the file!"};
            //cout<<current_byte<<" ";
            MS_DOS_HEADER_BUFFER[iter] = char_to_decimal(current_byte);
            iter++;
        }
        //cout<<"END OF DOS\n";
        return MS_DOS_HEADER_BUFFER;
    }

    int getPE_offset(){
        //cout<<"\nREADING PE_offset\n";
        int* dos_header = this->getMS_DOS_HEADER(); // size is 64
        int offset = 0;
        for(int i = 60; i < 64; i++){
            offset += pow(256, i - 60) * dos_header[i];
        }
        //cout<<"END of PE_offset\n";
        return offset;
    }




    int* getPE_HEADER() { // 24 bytes 4 - signature, 20 - other info
        int offset = getPE_offset();
        file1.seekg(offset, std::ios::beg);

        char current_byte;
        int iter{0};
        cout<<"PE IS: \n";
        while (iter < 24) {
            if(!file1.get(current_byte))
                throw std::invalid_argument{"Can't read the file!"};
            PE_HEADER_BUFFER[iter] = char_to_decimal(current_byte);
            cout<<std::hex<<PE_HEADER_BUFFER[iter]<<" ";
            iter++;
        }
        cout<<"\nPE END \n";

        return PE_HEADER_BUFFER;
    }

    void print(int pos, int cnt){
        file1.seekg(pos, std::ios::beg);
        cout<<"START print in "<<pos<<" "<<cnt<<std::endl;
        while(cnt--){
            char byte;
            file1.get(byte);
            cout<<byte<<" ";
        }
        cout<<"END of print\n";
    }

private:
    int pe_cur{0};

    std::string filename;
    std::ifstream file1;
    int* MS_DOS_HEADER_BUFFER = new int[64];
    int* PE_HEADER_BUFFER = new int[24];
    int* SIGNATURE_ANALYSIS = new int[300];
};


int main(int argc, char** argv) {
    std::cout << "START" << std::endl;


    Signature sig1("gamemd.exe");
    int x = sig1.getPE_offset();
    sig1.print(x, 2);
    int* pe = sig1.getPE_HEADER();
    cout<<pe[6]<<" "<<pe[7];

    Signature sig2("test_virus.exe");
    sig2.getPE_offset();
    x = sig2.getPE_offset();
    sig2.print(x, 2);
    pe = sig2.getPE_HEADER();
    cout<<pe[6]<<" "<<pe[7];

    std::cout << std::endl << "END OF SCAN" << std::endl;


    return 0;
}