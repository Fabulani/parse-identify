#include <iostream>
#include <fstream>
#include <cstring>

#define SMART_SELF_TEST_SUPPORTED 2 // Bitflag for SMART self-test support, bit 1 of word 87.

int main(int argc, char *argv[])
{
	// TODO: add --help

	if (argc < 2)
	{
		std::cerr << "Usage: " << argv[0] << " <input_file>" << std::endl;
		return 1;
	}

	// TODO: file type checks (.bin)
	std::string filename = argv[1];

	std::cout << "Opening file: " << filename << std::endl;

	const int word_size_bytes = 2;								// 2 bytes per word
	const int model_number_start_bytes = 27 * word_size_bytes;	// 27th word
	const int model_number_size_bytes = 20 * word_size_bytes;	// 20 words
	const int supported_dma_start_bytes = 88 * word_size_bytes; // 88th word
	const int supported_dma_size_bytes = 1 * word_size_bytes;
	const int smart_start_bytes = (87 * word_size_bytes) + 1; // 87th word, bits 0-7
	const int smart_size_bytes = 1;							  // LSB of 87th word

	std::ifstream file(filename, std::ios::binary | std::ios::ate); // ios::ate so pointer starts at end of file to get its size

	if (file.is_open())
	{
		// process file
		// TODO: check that binary file is 512-byte long
		int size_bytes = static_cast<int>(file.tellg());
		std::cout << "File size: " << size_bytes << " bytes" << std::endl;

		char buffer[size_bytes];
		file.seekg(0, std::ios::beg);
		file.read(buffer, size_bytes);
		file.close();

		// Model number - words 27-46 (little-endian)
		char model_number_buffer[model_number_size_bytes];
		std::memcpy(model_number_buffer, buffer + model_number_start_bytes, model_number_size_bytes);
		std::string model_number;

		for (int i = 0; i < model_number_size_bytes; i += word_size_bytes)
		{
			model_number += model_number_buffer[i + 1];
			model_number += model_number_buffer[i];
		}
		// Model number has trailing white space from leftover bytes. Remove them.
		model_number.erase(model_number.find_last_not_of(' ') + 1);

		std::cout << std::endl
				  << "--- ATA IDENTIFY ---" << std::endl;

		std::cout << "Model Number: " << model_number << std::endl;

		// Supported Ultra DMA modes, bits 0-7, MSB first
		char supported_dma_buffer[supported_dma_size_bytes];
		std::memcpy(supported_dma_buffer, buffer + supported_dma_start_bytes, supported_dma_size_bytes);

		// IntegerLogObvious: https://graphics.stanford.edu/~seander/bithacks.html#IntegerLogObvious
		unsigned int v = static_cast<unsigned int>(supported_dma_buffer[1]); // LSB contains the supported dma modes
		unsigned r = 0;														 // Counter for bit shifts, also lg(v).

		while (v)
		{
			v >>= 1;
			r++;
		}
		// r-1 is the highest supported mode
		// TODO: figure out a cleaner way to pretty print.
		if (r == 0)
			std::cout << "No Ultra DMA modes supported." << std::endl;
		else if (r == 1)
			std::cout << "Ultra DMA mode " << r - 1 << " is supported." << std::endl;
		else if (r > 7)
			std::cerr << "Error: r > 7 despite bit 7 being reserved. This should not happen." << std::endl;
		else
			std::cout << "Ultra DMA modes " << r - 1 << " and below are supported." << std::endl;

		// SMART self-test support is in LSB of word 87, bit 1.
		// TODO: check if the buffer is assigned the correct byte. Use bitset to double-check.
		unsigned char smart_buffer[1];
		std::memcpy(smart_buffer, buffer + smart_start_bytes, smart_size_bytes);
		if ((smart_buffer[0] & SMART_SELF_TEST_SUPPORTED) == SMART_SELF_TEST_SUPPORTED)
			std::cout << "SMART self-test supported." << std::endl;
		else
			std::cout << "SMART self-test not supported." << std::endl;
	}
	else
	{
		std::cerr << "Unable to open file: " << filename << std::endl;
		return 1;
	}
	return 0;
}