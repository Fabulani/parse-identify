#include "parser.h"

#include <fstream>

// TODO: it'd be better to define parser as a class and store the file buffer as read-only.
// TODO: good idea to put `read_file_to_buffer` in the constructor so it throws immediatelly if the file is not valid.

std::array<char, ATA_IDENTIFY_SIZE> read_file_to_buffer(const std::string &file_path)
{
    // Throw error if the file extension is not .bin
    std::string file_ext = file_path.substr(file_path.find_last_of("."));
    if (file_ext != ".bin")
    {
        throw std::runtime_error("Error: expected a binary file (.bin), but got (" + file_ext + ") instead.");
    }

    std::ifstream file(file_path, std::ios::binary | std::ios::ate); // ios::ate so pointer starts at end of file to get its size

    // Throw error if unable to open file
    if (!file.is_open())
    {
        throw std::runtime_error("Error: unable to open file. Does it exist and have correct access permissions?");
    }

    std::array<char, ATA_IDENTIFY_SIZE> file_buffer;
    const std::size_t FILE_SIZE = static_cast<int>(file.tellg());

    // Throw error if the file is not 512 bytes
    if (FILE_SIZE != 512)
    {
        throw std::runtime_error("Error: expected 512 bytes when reading the file, but got " + std::to_string(FILE_SIZE) + " bytes instead.");
    }

    file.seekg(0, std::ios::beg);
    file.read(file_buffer.data(), file_buffer.size());
    file.close();
    return file_buffer;
}

std::string extract_model_number(std::array<char, ATA_IDENTIFY_SIZE> &file_buffer)
{
    // Model number is in words 27-46. Note: the word pairs are little-endian.
    constexpr std::size_t START_BYTES = 54; // 27th word
    constexpr std::size_t SIZE_BYTES = 40;  // 20 words long

    char buffer[SIZE_BYTES];
    std::memcpy(buffer, file_buffer.data() + START_BYTES, SIZE_BYTES);
    std::string model_number;

    // 2-word pairs are little endian, so we must flip them
    for (int i = 0; i < SIZE_BYTES; i += 2)
    {
        model_number += buffer[i + 1];
        model_number += buffer[i];
    }
    // Model number has trailing white space from leftover bytes. Remove them.
    model_number.erase(model_number.find_last_not_of(' ') + 1);
    return model_number;
}

unsigned int extract_dma_mode(std::array<char, ATA_IDENTIFY_SIZE> &file_buffer)
{
    // Supported Ultra DMA modes are in the 88th word, bits 0-7.
    constexpr std::size_t START_BYTES = 176; // 88th word

    // IntegerLogObvious: https://graphics.stanford.edu/~seander/bithacks.html#IntegerLogObvious
    unsigned int lsb = static_cast<unsigned int>(file_buffer[START_BYTES]); // LSB contains the supported dma modes
    unsigned int bit_shifts = 0;                                            // Also lg(lsb).

    while (lsb)
    {
        lsb >>= 1;
        bit_shifts++;

        // Bit 7 is reserved, so we stop here.
        if (bit_shifts == 7)
        {
            break;
        }
    }

    unsigned int highest_supported_mode = bit_shifts - 1;
    return highest_supported_mode;
}

bool extract_smart_support(std::array<char, ATA_IDENTIFY_SIZE> &file_buffer)
{
    // SMART self-test support (from 'Command set/feature enabled/supported') is in word 87, bit 1.
    constexpr std::size_t START_BYTES = 174; // 87th word

    // Bitflag for bit 1 (LSB)
    constexpr uint16_t SMART_SELF_TEST_SUPPORTED_BITMASK = 0b00000010;

    bool smart_supported = (file_buffer[START_BYTES] & SMART_SELF_TEST_SUPPORTED_BITMASK) != 0;
    return smart_supported;
}
