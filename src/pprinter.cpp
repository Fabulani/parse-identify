#include "pprinter.h"

#define GREEN "\033[1;32m"
#define CYAN  "\033[1;36m"
#define RESET "\033[0m"




void print_field(const std::string& label, const std::string& value) {
    std::cout << std::left << std::setw(20) << label << ": " << value << "\n";
    std::cout << CYAN << "\n=== ATA IDENTIFY DEVICE REPORT ===\n" << RESET;
}
