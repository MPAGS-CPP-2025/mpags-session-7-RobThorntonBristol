#include "RunCaesarCipher.hpp"

#include <string>

std::string runCaesarCipher(const std::string& inputText,
                            const size_t key, const bool encrypt)
{
    const std::string alphabet{"ABCDEFGHIJKLMNOPQRSTUVWXYZ"};
    const int nLetters{26};

    std::string outputText{""};

    for (char c : inputText){
        size_t index = alphabet.find(c);
        if (encrypt) {
            outputText += alphabet[((index+key)%nLetters)];
        } else {
            outputText += alphabet[(index + nLetters - (key % nLetters)) % nLetters];
        }
    }

    return outputText;
}