#include "CSVParser.h"
#include <iostream>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "CSVParser <filename>" << std::endl;
        std::cerr << "Provide file to parse." << std::endl;
        exit(EXIT_FAILURE);
    }

    std::string filename = argv[1];
    
    CSVParser parser;
    parser.ParseFile(filename, ",");
    parser.PrintTable();
    return 0;
}
