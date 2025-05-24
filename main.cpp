#include <iostream>
#include <fstream>
#include <string>
#include <array>

#define SMART_SELF_TEST_SUPPORTED 2 // Bitflag for SMART self-test support, bit 1 of word 87.

const int ATA_IDENTIFY_SIZE = 512; // ATA IDENTIFY data structure size in bytes

int main(int argc, char *argv[])
{
	// Check if the user provided an argument.
	if (argc != 2 || std::string(argv[1]) == "--help" || std::string(argv[1]) == "-h")
	{
		const std::string error_log = "Usage: " + std::string(argv[0]) + " file_path\n";
		std::cerr << error_log;
		return 1;
	}

	std::string file_path = argv[1];

	// Check if the file extension is .bin. Return error if not.
	std::string file_ext = file_path.substr(file_path.find_last_of("."));
	if (file_ext != ".bin")
	{
		const std::string error_log = "Error: expected a binary file (.bin), but got (" + file_ext + ") instead.\n";
		std::cerr << error_log;
		return 1;
	}

	std::cout << "Opening file: " << file_path << std::endl;

	// TODO: move these constants to the parser header file.
	const int word_size_bytes = 2;								// 2 bytes per word
	const int model_number_start_bytes = 27 * word_size_bytes;	// 27th word
	const int model_number_size_bytes = 20 * word_size_bytes;	// 20 words
	const int supported_dma_start_bytes = 88 * word_size_bytes; // 88th word
	const int supported_dma_size_bytes = 1 * word_size_bytes;
	const int smart_start_bytes = (87 * word_size_bytes) + 1; // 87th word, bits 0-7
	const int smart_size_bytes = 1;							  // LSB of 87th word

	std::ifstream file(file_path, std::ios::binary | std::ios::ate); // ios::ate so pointer starts at end of file to get its size

	// Raise error if unable to open file
	if (!file.is_open())
	{
		std::cerr << "Error: unable to open file. Does it exist and have correct access permissions?\n";
		return 1;
	}

	std::array<char, ATA_IDENTIFY_SIZE> buffer; // Buffer for all the 512 bytes of data
	const int SIZE_BYTES = static_cast<int>(file.tellg());

	// Raise error if the file is not 512 bytes
	if (SIZE_BYTES != 512)
	{
		const std::string error_log = "Error: expected 512 bytes when reading the file, but got " + std::to_string(SIZE_BYTES) + " bytes instead.\n";
		std::cerr << error_log;
		return 1;
	}

	// Load file contents into the buffer
	file.seekg(0, std::ios::beg);
	file.read(buffer.data(), buffer.size());
	file.close();

	// Model number - words 27-46 (little-endian)
	char model_number_buffer[model_number_size_bytes];
	std::memcpy(model_number_buffer, buffer.data() + model_number_start_bytes, model_number_size_bytes);
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
	std::memcpy(supported_dma_buffer, buffer.data() + supported_dma_start_bytes, supported_dma_size_bytes);

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
	std::memcpy(smart_buffer, buffer.data() + smart_start_bytes, smart_size_bytes);
	if ((smart_buffer[0] & SMART_SELF_TEST_SUPPORTED) == SMART_SELF_TEST_SUPPORTED)
		std::cout << "SMART self-test supported." << std::endl;
	else
		std::cout << "SMART self-test not supported." << std::endl;

	return 0;
}