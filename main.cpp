#include <iostream>
#include <string>
#include <array>

#include "src/parser.h"


int main(int argc, char *argv[])
{
	// Check if the user provided an argument.
	if (argc != 2 || std::string(argv[1]) == "--help" || std::string(argv[1]) == "-h")
	{
		const std::string error_message = "Usage: " + std::string(argv[0]) + " file_path\n";
		std::cerr << error_message;
		return 1;
	}

	std::string file_path = argv[1];

	std::cout << "Opening file: " << file_path << std::endl;

	std::array<char, ATA_IDENTIFY_SIZE> file_buffer = read_file_to_buffer(file_path);

	std::cout << "File successfully opened.\n";

	// Parse the file buffer
	std::string model_number = extract_model_number(file_buffer);
	unsigned int highest_dma_mode = extract_dma_mode(file_buffer);
	bool smart_support = extract_smart_support(file_buffer);

	std::cout << std::endl
			  << "--- ATA IDENTIFY ---" << std::endl;

	std::cout << "Model Number: " << model_number << std::endl;
	if (highest_dma_mode == 0)
		std::cout << "Ultra DMA mode " << highest_dma_mode << " is supported." << std::endl;
	else
		std::cout << "Ultra DMA modes " << highest_dma_mode << " and below are supported." << std::endl;

	if (smart_support)
		std::cout << "SMART self-test supported." << std::endl;
	else
		std::cout << "SMART self-test not supported." << std::endl;

	return 0;
}