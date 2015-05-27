#ifndef SPN_H
#define SPN_H

#include <string>

class SPN {
public:
    SPN(std::string);
    SPN(std::string, std::string, std::string);
    std::string encryptMessage(std::string, unsigned);
    unsigned bits_to_unsigned(std::string&, unsigned);

private:
    void xor_key(std::string&, unsigned);
    void substitution_box(std::string&);
    void permutation_box(std::string&);

    std::string key;
    std::string SB;
    std::string PB;
};

#endif