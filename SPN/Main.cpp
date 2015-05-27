#include "main.h"

int main() {
    try {
        SPN spn("11100111011001111001000000111101");
        std::string encryptedBinaryMessage = spn.encryptMessage("0100111010100001", 3);
        std::vector<unsigned> encryptedMessage = binary2char(encryptedBinaryMessage);
        for (unsigned value : encryptedMessage) {
            std::cout << value << std::endl;
        }
    } catch (std::string e) {
        std::cout << e;
    }

    return 0;
}

std::vector<unsigned> binary2char(std::string binary) {
    if (!validateBinaryString(binary)) {
        throw std::string("Invalid binary data provided");
    }

    //4 bit alignment
    for (unsigned index = 0; index < binary.size() % 4; ++index) {
        binary = "0" + binary;
    }

    std::vector<unsigned> plainText;
    for (unsigned characterIndex = 0; characterIndex < binary.size(); characterIndex += 4) {
        unsigned character = 0;
        for (unsigned bitIndex = 0; bitIndex < 4; ++bitIndex) {
            character = character << 1;
            if (binary[characterIndex + bitIndex] == '1') {
                ++character;
            }
        }
        plainText.push_back(character);
    }
    return plainText;
}