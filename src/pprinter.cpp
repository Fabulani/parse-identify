#include "pprinter.h"

void print_results(const std::string &file_path,
                   const std::string &model_number,
                   unsigned int highest_dma_mode, bool smart_supported) {
  const std::size_t COLUMN_WIDTH = 30;

  print_header("ATA IDENTIFY RESULTS", COLUMN_WIDTH * 2);

  print_row("File", file_path, WHITE, COLUMN_WIDTH);
  print_row("Status", "Successfully opened", GREEN, COLUMN_WIDTH);

  print_div(CYAN, COLUMN_WIDTH * 2);

  print_row("Model Number", model_number, WHITE, COLUMN_WIDTH);
  print_row("Supported Ultra DMA Modes",
            highest_dma_mode ? std::to_string(highest_dma_mode) + " and below"
                             : std::to_string(highest_dma_mode),
            WHITE, COLUMN_WIDTH);
  print_row("SMART Self-Test Support", smart_supported ? "Yes" : "No",
            smart_supported ? GREEN : RED, COLUMN_WIDTH);

  print_div(CYAN, COLUMN_WIDTH * 2);
}

void print_header(const std::string &title, const std::size_t width) {
  int pad_left = (width - static_cast<int>(title.length())) / 2;

  // Avoid negative padding if title is too wide
  if (pad_left < 0)
    pad_left = 0;

  std::cout << CYAN << std::string(width, '=') << RESET << "\n";
  std::cout << CYAN << std::string(pad_left, ' ') << title << RESET << "\n";
  std::cout << CYAN << std::string(width, '=') << RESET << "\n";
}

void print_row(const std::string &label, const std::string &value,
               const std::string &color, const std::size_t column_width) {
  std::cout << std::left << std::setw(column_width) << label << ": " << color
            << value << RESET << "\n";
}

void print_div(const std::string &color, const std::size_t width) {
  std::cout << color << std::string(width, '-') << RESET << "\n";
}