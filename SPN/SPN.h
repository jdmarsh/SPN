#ifndef SPN_H
#define SPN_H

#include <vector>
#include <string>

std::vector<unsigned> binary2char(std::string);
bool validateBinaryString(std::string);

class SPN {
public:
    SPN(std::string);
    SPN(std::string, std::string, std::string);
    std::string encryptMessage(std::string, unsigned);

private:
    void xor(std::string&, unsigned);
    void substitutionBox(std::string&);
    void permutationBox(std::string&);
    unsigned getUnsignedCharacter(std::string&, unsigned);

    std::string key;
    std::string SB;
    std::string PB;
};

#endif