#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>   // To help with splitting the CSV line
#include <CLI11/CLI.hpp>  // CLI11 for command line arguments

// Function to split a string by a delimiter (used to split CSV rows)
std::vector<std::string> split_line(const std::string &line, char delimiter = ',') {
    std::vector<std::string> result;
    std::stringstream ss(line);
    std::string token;
    
    while (std::getline(ss, token, delimiter)) {
        result.push_back(token);
    }
    
    return result;
}

int main(int argc, char *argv[]) {
    CLI::App app{"CSV File Reader"};

    // Command line option to accept the input file
    std::string input_file;
    app.add_option("-i,--input-file", input_file, "Input CSV file")
        ->required();

    // Parse the command line arguments
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
    int line_count = 0;  // Counter to track how many lines we read

    // Read the header line first if necessary
    if (std::getline(file, line)) {
        std::vector<std::string> header = split_line(line);
        std::cout << "Header: ";
        for (const auto &col : header) {
            std::cout << col << " ";
        }
        std::cout << std::endl;
    }

    // Read each remaining row
    while (std::getline(file, line)) {
        std::vector<std::string> row = split_line(line);
        std::cout << "Row " << line_count << ": ";
        for (const auto &col : row) {
            std::cout << col << " ";
        }
        std::cout << std::endl;
        line_count++;
    }

    if (line_count == 0) {
        std::cout << "The file is empty or could not be read." << std::endl;
    }

    file.close();
    return 0;
}
