#include "Main.h"

int main() {
    Text pt{ { 1, 1, 1, 1 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } };
    for (unsigned i = 0; i < 3; ++i) {
        pt.keyxor(i);
        pt.Sbox();
        pt.Pbox();
    }
    pt.keyxor(3);
    pt.Sbox();
    pt.keyxor(4);
    std::cout << pt.btou(0) << "," << pt.btou(1) << "," << pt.btou(2) << "," << pt.btou(3) << std::endl;
    return 0;
}