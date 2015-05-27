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