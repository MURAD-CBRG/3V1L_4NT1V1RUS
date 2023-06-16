#ifndef SIGNATURE_H
#define SIGNATURE_H

#include <iostream>
#include <fstream>
#include <cmath>
#include <filesystem>
#include <string>
#include <cstring>
#include <algorithm>
#include <vector>

#include "sha256/sha256.h"

/**
 * \brief A class for reading the headers of a Windows executable and calculating its SHA256 hash value.
 */
class Signature
{
public:
    /**
     * \brief Constructs a new Signature object for the given file.
     * \param filename The path of the file to be read.
     *
     * This constructor creates a new Signature object for the given file and reads PE and MS_DOS headers of file.
     */
    Signature(std::string filename);

    /**
     * \brief Destroys the Signature object and closes the file.
     *
     * This destructor destroys the Signature object and closes the file associated with it.
     */
    ~Signature();

    /**
     * \brief Returns the offset of the PE header in the file.
     * \return The offset of the PE header in the file.
     */
    int get_PE_offset();

    /**
     * \brief Returns the offset of the section headers in the file.
     * \return The offset of the section headers in the file.
     */
    int get_Sections_offset();

    /**
     * \brief Returns the number of sections in the headers of the file.
     * \return The number of sections in the headers of the file.
     */
    int get_number_of_sections();

    /**
     * \brief Prints the first `cnt` bytes starting from the given position.
     * \param cnt The number of bytes to print.
     * \param pos The position to start printing from.
     */
    void print(unsigned cnt, int pos);

    /**
     * \brief Sums up the bytes of the file starting from the given position.
     * \param size The number of the bytes to sum up.
     * \param pos The position to start summing up from.
     * \return The sum of the bytes.
     */
    int sum_up_bytes(unsigned short size, int pos);

    /**
     * \brief Calculates the SHA256 hash value of the file.
     * \return The SHA256 hash value of the file.
     */
    std::string get_hash();
private:
    /**
     * \brief Reads the MS-DOS header of the file.
     *
     * This function reads the MS-DOS header of the file and stores it in the MS_DOS_HEADER_BUFFER vector.
     */
    void read_MS_DOS_HEADER();

    /**
     * \brief Reads the PE header of the file.
     *
     * This function reads the PE header of the file and stores it in the PE_HEADER_BUFFER vector.
     */
    void read_PE_HEADER();

    std::string filename; /**< The path of the file. */
    std::ifstream file; /**< An ifstream object for reading the file. */
    std::vector<unsigned char> MS_DOS_HEADER_BUFFER; /**< The MS-DOS header of the file. */
    std::vector<unsigned char> PE_HEADER_BUFFER; /**< The PE header of the file. */
};

#endif
