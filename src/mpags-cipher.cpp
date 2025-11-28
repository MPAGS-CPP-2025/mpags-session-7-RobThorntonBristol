#include "ProcessCommandLine.hpp"
#include "TransformChar.hpp"

#include <cctype>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

int main(int argc, char* argv[])
{
    // Convert the command-line arguments into a more easily usable form
    const std::vector<std::string> cmdLineArgs{argv, argv + argc};

    // Options that might be set by the command-line arguments
    bool helpRequested{false};
    bool versionRequested{false};
    std::string inputFile{""};
    std::string outputFile{""};
    bool encrypt{true};
    std::size_t cipherkey;

    // Process command line arguments
    const bool cmdLineStatus{processCommandLine(
        cmdLineArgs, helpRequested, versionRequested, inputFile, outputFile, encrypt, cipherkey)};

    std::string runCaesarCipher(const std::string& inputText, const std::size_t cipherkey, 
                                const bool encrypt);

    // Any failure in the argument processing means we can't continue
    // Use a non-zero return value to indicate failure
    if (!cmdLineStatus) {
        return 1;
    }

    // Handle help, if requested
    if (helpRequested) {
        // Line splitting for readability
        std::cout
            << "Usage: mpags-cipher [-h/--help] [--version] [-i <file>] [-o <file>]\n\n"
            << "Encrypts/Decrypts input alphanumeric text using classical ciphers\n\n"
            << "Available options:\n\n"
            << "  -h|--help        Print this help message and exit\n\n"
            << "  --version        Print version information\n\n"
            << "  -i FILE          Read text to be processed from FILE\n"
            << "                   Stdin will be used if not supplied\n\n"
            << "  -o FILE          Write processed text to FILE\n"
            << "                   Stdout will be used if not supplied\n\n"
            << "  --encrypt        Set cipher mode to encrypt input text\n\n"
            << "  --decrypt        Set cipher mode to decrypt input text\n\n"
            << "  --key            The cipher key to encrypt and decrypt text\n\n"
            << std::endl;
        // Help requires no further action, so return from main
        // with 0 used to indicate success
        return 0;
    }

    // Handle version, if requested
    // Like help, requires no further action,
    // so return from main with zero to indicate success
    if (versionRequested) {
        std::cout << "0.1.0" << std::endl;
        return 0;
    }

    // Initialise variables
    char inputChar{'x'};
    std::string inputText;
    std::string inputTextciphered{""};

    // Read in user input from stdin/file
    // Warn that input file option not yet implemented
    if (!inputFile.empty()) {
        std::ifstream in_file {inputFile};
        bool ok_to_read = in_file.good();
        if (ok_to_read) {
            std::cout << "Successfuly read input file" << std::endl;
        } else {
            std::cerr << "[warning] input from file ('" << inputFile
                    << "') not read properly, closing program\n";
            return 1;
        }
        while (in_file >> inputChar) {
            inputText += transformChar(inputChar);
        }
        in_file.close();
        inputTextciphered = runCaesarCipher(inputText, cipherkey, encrypt);
        std::ofstream  out_file {outputFile};
        bool ok_to_write = out_file.good();
        if (ok_to_write) {
            out_file << inputTextciphered;
            out_file.close();
        }
    } else {
        std::cout << "No input file given, using stdin\n";
        while (std::cin >> inputChar) {
        if (inputFile.empty())
            inputText += transformChar(inputChar);
    } 
        // Print out the transliterated text
        std::cout << inputText << std::endl;
        }
    



    // No requirement to return from main, but we do so for clarity
    // and for consistency with other functions
    return 0;
}
