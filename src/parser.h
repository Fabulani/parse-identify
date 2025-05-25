#pragma once
#include <algorithm>
#include <array>
#include <fstream>
#include <string>

constexpr std::size_t ATA_IDENTIFY_SIZE =
    512; // ATA IDENTIFY data structure size in bytes

// Reads a file into a buffer. Checks if the file is binary, has 512 bytes, and
// is opened successfully.
std::array<char, ATA_IDENTIFY_SIZE>
read_file_to_buffer(const std::string &file_path);

// Parser functions for extracting specific information from the file buffer.
std::string
extract_model_number(std::array<char, ATA_IDENTIFY_SIZE> &file_buffer);
unsigned int extract_dma_mode(std::array<char, ATA_IDENTIFY_SIZE> &file_buffer);
bool extract_smart_support(std::array<char, ATA_IDENTIFY_SIZE> &file_buffer);
