#ifndef MPAGSCIPHER_PROCESSCOMMANDLINE_HPP
#define MPAGSCIPHER_PROCESSCOMMANDLINE_HPP

#include <string>
#include <vector>

bool processCommandLine(const std::vector<std::string>& cmdLineArgs,
                        bool& helpRequested, bool& versionRequested,
                        std::string& inputFile, std::string& outputFile,
                        bool& encrypt, std::size_t& cipherkey);

#endif    // MPAGSCIPHER_PROCESSCOMMANDLINE_HPP