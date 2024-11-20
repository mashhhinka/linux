#include <iostream>
#include <fstream>
#include <string>

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <source-file> <destination-file>\n";
        return 1;
    }

    std::string sourceFile = argv[1];
    std::string destFile = argv[2];

    std::ifstream source(sourceFile, std::ios::binary);
    if (!source) {
        std::cerr << "Error: Could not open source file '" << sourceFile << "'.\n";
        return 1;
    }

    std::ofstream dest(destFile, std::ios::binary);
    if (!dest) {
        std::cerr << "Error: Could not open or create destination file '" << destFile << "'.\n";
        return 1;
    }

    dest << source.rdbuf();

    if (!dest) {
        std::cerr << "Error: Failed to write to destination file.\n";
        return 1;
    }

    std::cout << "File copied successfully from '" << sourceFile << "' to '" << destFile << "'.\n";
    return 0;
}
