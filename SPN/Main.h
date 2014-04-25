#pragma once
#ifndef SPN_MAIN_H
#define SPN_MAIN_H

#include <iostream>
#include <vector>
#include <array>

class text {
public:
    text(std::initializer_list<unsigned>);
    unsigned bits_to_unsigned(unsigned);
    void xor_key(unsigned);
    void substitution_box();
    void permutation_box();

private:
    static const std::array<unsigned, 16> SB;
    static const std::array<unsigned, 16> PB;

    std::vector<unsigned> key;
    std::vector<unsigned> bits;
};

const std::array<unsigned, 16> text::SB = { 4, 1, 14, 8, 13, 6, 2, 11,
                                            15, 12, 9, 7, 3, 10, 5, 0 };
const std::array<unsigned, 16> text::PB = { 0, 4, 8, 12, 1, 5, 9, 13,
                                            2, 6, 10, 14, 3, 7, 11, 15 };

text::text(std::initializer_list<std::initializer_list<unsigned>> list)
{
    for (auto it : list) {
        bits.emplace_back(it);
    }
    key = { 1, 1, 1, 0, 0, 1, 1, 1, 0, 1, 1, 0, 0, 1, 1, 1,
    1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 1 };
}

unsigned text::bits_to_unsigned(unsigned i)
{
    return (bits[i * 4] * 8) + (bits[(i * 4) + 1] * 4) +
        (bits[(i * 4) + 2] * 2) + bits[(i * 4) + 3];
}

void text::xor_key(unsigned round)
{
    for (unsigned i = 0; i < 16; ++i) {
        bits[i] ^= key[(round * 4) + i];
    }
}

void text::substitution_box()
{
    for (unsigned i = 0; i < 4; ++i) {
        unsigned x = SB[btou(i)];
        bits[i*4] = (x & 0x8) >> 3;
        bits[(i*4)+1] = (x & 0x4) >> 2;
        bits[(i*4)+2] = (x & 0x2) >> 1;
        bits[(i*4)+3] = x & 0x1;
    }
}

void text::permutation_box()
{
    for (unsigned i = 0; i < 16; ++i) {
        if (i <= PB[i]) {
            unsigned temp = bits[i];
            bits[i] = bits[PB[i]];
            bits[PB[i]] = temp;
        }
    }
}

#endif // SPN_MAIN_H