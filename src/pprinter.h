#pragma once
#include <iomanip>
#include <iostream>
#include <string>

// ANSI color escape codes for terminal output. 
const std::string RED = "\033[31m";
const std::string GREEN = "\033[32m";
const std::string CYAN = "\033[36m";
const std::string WHITE = "\033[37m";
const std::string RESET = "\033[0m";

// Wrapper for print_(header, row, div) that nicely prints the results of parsing an ATA IDENTIFY results file
void print_results(const std::string &file_path, const std::string &model_number,
                   unsigned int highest_dma_mode, bool smart_supported);

void print_header(const std::string &title, const std::size_t width);

void print_row(const std::string &label, const std::string &value, const std::string &color, const std::size_t column_width);

void print_div(const std::string &color, const std::size_t width);