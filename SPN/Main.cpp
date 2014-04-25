#include "main.h"

int main() {
    text pt{ 0, 1, 0, 0, 1, 1, 1, 0, 1, 0, 1, 0, 0, 0, 0, 1 };
    for (unsigned i = 0; i < 3; ++i) {
        pt.xor_key(i);
        pt.substitution_box();
        pt.permutation_box();
    }
    pt.xor_key(3);
    pt.substitution_box();
    pt.xor_key(4);

    std::cout << pt.bits_to_unsigned(0) << "," << pt.bits_to_unsigned(1) << ","
        << pt.bits_to_unsigned(2) << "," << pt.bits_to_unsigned(3)
        << std::endl;

    return 0;
}