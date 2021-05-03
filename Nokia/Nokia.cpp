#include "CSVParser.h"
#include <iostream>
#include "Exceptions.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "CSVParser <filename>" << std::endl;
        std::cerr << "Provide file to parse." << std::endl;
        exit(EXIT_FAILURE);
    }

    std::string filename = argv[1];
    
    CSVParser parser;
    try {
        parser.ParseFile(filename, ",");
    }
    catch (std::exception& e) {
        std::cout << e.what() << std::endl;
        exit(EXIT_FAILURE);
    }

    try {
        parser.PrintTable();
    }
    catch (std::exception& e) {
        std::cout << std::endl;
        std::cout << e.what() << std::endl;
        exit(EXIT_FAILURE);
    }
    return 0;
}
