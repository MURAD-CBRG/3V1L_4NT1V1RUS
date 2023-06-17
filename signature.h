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
 * \class Signature
 * \brief A class for reading the headers of a Windows executable and calculating its SHA256 hash value.
 */
class Signature
{
public:
    /**
     * \brief Constructor which takes a file name as an argument and opens the file in binary mode. The constructor reads the MS-DOS header and PE header of the file.
     *
     * \param filename The name of the file to open.
     *
     * \throws std::ifstream::failure If the file cannot be opened.
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
     *
     * \return The offset of the PE header in the file.
     */
    int get_PE_offset();

    /**
     * \brief Returns the offset of the section headers in the file.
     *
     * \return The offset of the section headers in the file.
     */
    int get_Sections_offset();

    /**
     * \brief Returns the number of sections in the headers of the file.
     *
     * \return The number of sections in the headers of the file.
     */
    int get_number_of_sections();

    /**
     * \brief Reads the specified number of bytes from the file at the given position, and returns the sum of the bytes computed as an integer.
     *
     * \param size The number of bytes to read.
     * \param pos The position in the file to start reading from.
     *
     * \throws std::invalid_argument If the size parameter is greater than 4.
     * \throws std::ifstream::failure If the file cannot be read.
     *
     * \return The sum of the bytes computed as an integer.
     */
    long int sum_up_bytes(unsigned short size, int pos = -1);

    /**
     * \brief Returns the SHA256 hash of the `.text` section of the file.
     *
     * The method uses the sum_up_bytes() function to compute the size and offset of the raw data of the `.text` section,
     * and then reads the raw data and computes its hash using the sha256() function.
     *
     * \throws std::ifstream::failure If the file cannot be read.
     *
     * \return The SHA256 hash of the `.text` section of the file.
     */
    std::string get_hash();

    /**
     * \brief Returns the MS-DOS header buffer.
     *
     * \return The MS-DOS header buffer.
     */
    std::vector<unsigned char> get_MS_DOS_HEADER_BUFFER() const;

    /**
     * \brief Returns the PE header buffer.
     *
     * \return The PE header buffer.
     */
    std::vector<unsigned char> get_PE_HEADER_BUFFER() const;

private:
    /**
     * \brief Reads the MS-DOS header of the file and checks that the file is an executable file.
     *
     * \throws std::invalid_argument If the file is not an executable file.
     * \throws std::ifstream::failure If the file cannot be read.
     */
    void read_MS_DOS_HEADER();

    /**
     * \brief Reads the PE header of the file and checks that the PE header exists.
     *
     * \throws std::invalid_argument If the PE header does not exist.
     * \throws std::ifstream::failure If the file cannot be read.
     */
    void read_PE_HEADER();

    std::string filename;                            /**< The path of the file. */
    std::ifstream file;                              /**< An ifstream object for reading the file. */
    std::vector<unsigned char> MS_DOS_HEADER_BUFFER; /**< The MS-DOS header of the file. */
    std::vector<unsigned char> PE_HEADER_BUFFER;     /**< The PE header of the file. */
};

#endif
