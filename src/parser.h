#pragma once
#include <string>
#include <array>

constexpr std::size_t ATA_IDENTIFY_SIZE = 512; // ATA IDENTIFY data structure size in bytes


std::array<char, ATA_IDENTIFY_SIZE> read_file_to_buffer(const std::string& file_path);

std::string extract_model_number(std::array<char, ATA_IDENTIFY_SIZE>& buffer);
unsigned int extract_dma_mode(std::array<char, ATA_IDENTIFY_SIZE>& buffer);
bool extract_smart_support(std::array<char, ATA_IDENTIFY_SIZE>& buffer);
