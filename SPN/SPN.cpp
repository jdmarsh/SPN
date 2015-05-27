#include "SPN.h"

unsigned ascii2decimal(char);

SPN::SPN(std::string binaryKey) {
    if (!validateBinaryString(binaryKey)) {
        throw std::string("Invalid binary key provided");
    }
    for (unsigned index = 0; index < binaryKey.size() % 4; ++index) {
        binaryKey = "0" + binaryKey;
    }
    key = binaryKey;
    SB = "41e8d62bfc973a50";
    PB = "048c159d26ae37bf";
}

SPN::SPN(std::string binaryKey, std::string subBox, std::string permBox) {
    if (!validateBinaryString(binaryKey)) {
        throw std::string("Invalid binary key provided");
    }
    if (subBox.size() != 16 || permBox.size() != 16) {
        throw std::string("Substitution and permutation boxes must both be 16 characters long");
    }
    //4 bit alignment
    for (unsigned index = 0; index < binaryKey.size() % 4; ++index) {
        binaryKey = "0" + binaryKey;
    }
    key = binaryKey;

    if (subBox.size() == 16) {
        SB = subBox;
    } else {
        SB = "41e8d62bfc973a50";
    }

    if (permBox.size() == 16) {
        PB = permBox;
    } else {
        PB = "048c159d26ae37bf";
    }
};

std::string SPN::encryptMessage(std::string message, unsigned itterations) {
    if (!validateBinaryString(message)) {
        throw std::string("Invalid binary message provided");
    }
    if (message.size() != 16) {
        throw std::string("Message length must be 16 bits");
    }
    if (key.size() < (16 + (4 * (itterations + 1)))) {
        throw std::string("Key length does not support this number of itterations for the message provided");
    }
    for (unsigned i = 0; i < itterations; ++i) {
        xor(message, i);
        substitutionBox(message);
        permutationBox(message);
    }
    xor(message, itterations);
    substitutionBox(message);
    xor(message, itterations + 1);
    return message;
}

unsigned SPN::getUnsignedCharacter(std::string& message, unsigned i) {
    unsigned result = 0;
    for (unsigned index = (i * 4); index < (i * 4) + 4; ++index) {
        result = result << 1;
        if (message[index] == '1') {
            ++result;
        }
    }
    return result;
}

void SPN::xor(std::string& message, unsigned round) {
    for (unsigned i = 0; i < 16; ++i) {
        bool messageBit = (message[i] == '1');
        bool keyBit = (key[(round * 4) + i] == '1');
        if (messageBit ^ keyBit) {
            message[i] = '1';
        } else {
            message[i] = '0';
        }
    }
}

void SPN::substitutionBox(std::string& message) {
    for (unsigned i = 0; i < 4; ++i) {
        unsigned x = ascii2decimal(SB[getUnsignedCharacter(message, i)]);
        for (unsigned j = 0; j < 4; ++j) {
            if (((x >> (3 - j)) & 0x1) > 0) {
                message[(i * 4) + j] = '1';
            } else {
                message[(i * 4) + j] = '0';
            }
        }
    }
}

void SPN::permutationBox(std::string& message) {
    for (unsigned i = 0; i < 16; ++i) {
        if (i <= ascii2decimal(PB[i])) {
            unsigned temp = message[i];
            message[i] = message[ascii2decimal(PB[i])];
            message[ascii2decimal(PB[i])] = temp;
        }
    }
}

bool validateBinaryString(std::string binary) {
    for (char bit : binary) {
        if (!(bit == '0' || bit == '1')) {
            return false;
        }
    }
    return true;
}

unsigned ascii2decimal(char character) {
    unsigned decimal = 0;
    if (character >= '0' && character <= '9') {
        decimal = static_cast<unsigned>(character - 48);
    } else if (character >= 'A' && character <= 'F') {
        decimal = static_cast<unsigned>(character - 55);
    } else if (character >= 'a' && character <= 'f') {
        decimal = static_cast<unsigned>(character - 87);
    }
    return decimal;
}