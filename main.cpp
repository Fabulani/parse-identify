#include <iostream>
#include <fstream>

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

	std::streampos size_bytes;							 // file size in bytes
	int word_size_bytes = 2;							 // 2 bytes per word
	int model_number_start_bytes = 27 * word_size_bytes; // 27th word
	int model_number_size_bytes = 20 * word_size_bytes;	 // 20 words

	std::ifstream file(filename, std::ios::binary | std::ios::ate); // ios::ate so pointer starts at end of file to get its size

	if (file.is_open())
	{
		// process file
		// TODO: check that binary file is 512-byte long
		size_bytes = file.tellg();
		std::cout << "File size: " << size_bytes << " bytes" << std::endl;

		// Model number - words 27-46 (little-endian)
		char raw_bytes[model_number_size_bytes];
		std::string model_number;
		file.seekg(model_number_start_bytes, std::ios::beg);
		file.read(raw_bytes, model_number_size_bytes);
		for (int i = 0; i < model_number_size_bytes; i += word_size_bytes)
		{
			model_number += raw_bytes[i + 1];
			model_number += raw_bytes[i];
		}
		// Model number has trailing white space from leftover bytes. Remove them.
		model_number.erase(model_number.find_last_not_of(' ') + 1);

		std::cout << "Model Number: " << model_number << std::endl;

		file.close();
	}
	else
	{
		std::cerr << "Unable to open file: " << filename << std::endl;
		return 1;
	}
	return 0;
}