#include "main.h"

int main() {
    SPN spn("11100111011001111001000000111101");
    std::string encryptedMessage = spn.encryptMessage("0100111010100001", 3);

    std::cout << spn.bits_to_unsigned(encryptedMessage, 0) << "," << spn.bits_to_unsigned(encryptedMessage, 1) << ","
        << spn.bits_to_unsigned(encryptedMessage, 2) << "," << spn.bits_to_unsigned(encryptedMessage, 3)
        << std::endl;

    return 0;
}