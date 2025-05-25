#include "parser.h"
#include "pprinter.h"

#include <array>
#include <iostream>
#include <string>

int main(int argc, char *argv[]) {
  // Check if the user provided an argument.
  if (argc != 2 || std::string(argv[1]) == "--help" ||
      std::string(argv[1]) == "-h") {
    const std::string error_message =
        "Usage: " + std::string(argv[0]) + " file_path\n";
    std::cerr << error_message;
    return 1;
  }

  std::string file_path = argv[1];
  std::array<char, ATA_IDENTIFY_SIZE> file_buffer =
      read_file_to_buffer(file_path);

  // Parse the file buffer
  std::string model_number = extract_model_number(file_buffer);
  unsigned int highest_dma_mode = extract_dma_mode(file_buffer);
  bool smart_supported = extract_smart_support(file_buffer);

  print_results(file_path, model_number, highest_dma_mode, smart_supported);
  return 0;
}