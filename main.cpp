#include <iostream>
#include <iomanip>
#include <cassert>
#include <vector>
#include "lvt.h"
#include "base256.h"

#define HEX(x) std::setw(2) << std::setfill('0') << std::hex << std::uppercase << (int)(x)

int main(int argc, char *argv[]) {
    assert(argc == 3);
    assert(argv[1][0] == 'e' || argv[1][0] == 'd');
    if(argv[1][0] == 'e') {
        std::vector<uint8_t> converted = base256::convert10to256(std::string(argv[2]));
        std::vector<uint8_t> encoded = lvt::encodeLength(converted);
        for(auto digit: encoded) {
            std::cout << HEX(digit);
        }
        std::cout << std::endl;
    }
    else {
        std::vector<uint8_t> converted = base256::convert16to256(std::string(argv[2]));
        std::vector<uint8_t> decoded = lvt::decodeLength(converted);
        std::string deconverted = base256::convert256to10(decoded);
        std::cout << deconverted << std::endl;
    }
    return 0;
}
