#include "SPN.h"

unsigned ascii2decimal(char);

SPN::SPN(std::string binaryKey) {
    //align key to 16 bits
    key = binaryKey;
    SB = "41e8d62bfc973a50";
    PB = "048c159d26ae37bf";
}

SPN::SPN(std::string binaryKey, std::string subBox, std::string permBox) {
    key = binaryKey;
    SB = subBox;
    PB = permBox;
};

std::string SPN::encryptMessage(std::string message, unsigned itterations) {
    //align message to 16 bits
    for (unsigned i = 0; i < itterations; ++i) {
        xor_key(message, i);
        substitution_box(message);
        permutation_box(message);
    }
    xor_key(message, itterations);
    substitution_box(message);
    xor_key(message, itterations + 1);
    return message;
}

unsigned SPN::bits_to_unsigned(std::string& message, unsigned i) {
    unsigned result = 0;
    for (unsigned index = (i * 4); index < (i * 4) + 4; ++index) {
        result = result << 1;
        if (message[index] == '1') {
            ++result;
        }
    }
    return result;
}

void SPN::xor_key(std::string& message, unsigned round) {
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

void SPN::substitution_box(std::string& message) {
    for (unsigned i = 0; i < 4; ++i) {
        unsigned x = ascii2decimal(SB[bits_to_unsigned(message, i)]);
        for (unsigned j = 0; j < 4; ++j) {
            if (((x >> (3 - j)) & 0x1) > 0) {
                message[(i * 4) + j] = '1';
            } else {
                message[(i * 4) + j] = '0';
            }
        }
    }
}

void SPN::permutation_box(std::string& message) {
    for (unsigned i = 0; i < 16; ++i) {
        if (i <= ascii2decimal(PB[i])) {
            unsigned temp = message[i];
            message[i] = message[ascii2decimal(PB[i])];
            message[ascii2decimal(PB[i])] = temp;
        }
    }
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