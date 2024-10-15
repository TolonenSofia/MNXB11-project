#include <iostream>
#include <fstream>
#include <string>
#include <CLI11/CLI.hpp>


int main(int argc, char *argv[]) {
    CLI::App app{"CSV File Reader"};

    std::string input_file;
    app.add_option("-i,--input-file", input_file, "Input CSV file")
        ->required();

    CLI11_PARSE(app, argc, argv);

    std::cout << "CSV file to process: " << input_file << std::endl;

    // Open the CSV file
    std::ifstream file(input_file);
    
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << input_file << std::endl;
        return 1;
    }

    std::cout << "File opened successfully!" << std::endl;

    // Read and output the file content line by line
    std::string line;
    int line_count = 0;  // Counter to check how many lines we read
    while (std::getline(file, line)) {
        std::cout << "Read line: " << line << std::endl;
        line_count++;
    }

    if (line_count == 0) {
        std::cout << "The file is empty or could not be read." << std::endl;
    }


    file.close();

    return 0;
}
