#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include <vector>

class Text {
private:
    std::vector<unsigned> SB;
    std::vector<unsigned> PB;
    std::vector<unsigned> key;
public:
    Text(std::initializer_list<unsigned>);
    unsigned btou(unsigned);
    void keyxor(unsigned);
    void Sbox();
    void Pbox();

    std::vector<unsigned> bits;
};

Text::Text(std::initializer_list<unsigned> list) {
    SB = { 4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0 };
    PB = { 0, 4, 8, 12, 1, 5, 9, 13, 2, 6, 10, 14, 3, 7, 11, 15 };
    for (auto it : list) {
        bits.push_back(it);
    }
    key = { 1, 1, 1, 0, 0, 1, 1, 1, 0, 1, 1, 0, 0, 1, 1, 1,
    1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 1 };
}

unsigned Text::btou(unsigned i) {
    return (bits[i*4] * 8) + (bits[(i*4)+1] * 4) +
        (bits[(i*4)+2] * 2) + bits[(i*4)+3];
}

void Text::keyxor(unsigned round) {
    for (unsigned i = 0; i < 16; ++i) {
            bits[i] ^= key[(round*4) + i];
    }
}

void Text::Sbox() {
    for (unsigned i = 0; i < 4; ++i) {
        unsigned x = SB[btou(i)];
        bits[i*4] = (x & 0x8) >> 3;
        bits[(i*4)+1] = (x & 0x4) >> 2;
        bits[(i*4)+2] = (x & 0x2) >> 1;
        bits[(i*4)+3] = x & 0x1;
    }
}

void Text::Pbox() {
    for (unsigned i = 0; i < 16; ++i) {
        if (i <= PB[i]) {
            unsigned temp = bits[i];
            bits[i] = bits[PB[i]];
            bits[PB[i]] = temp;
        }
    }
}

#endif