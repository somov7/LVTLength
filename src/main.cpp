#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <vector>
#include "lvt.h"
#include "base256.h"

#define HEX(x) std::setw(2) << std::setfill('0') << std::hex << std::uppercase << (int)(x)

int main(int argc, char *argv[]) {
    if(argc < 3) {
        throw std::invalid_argument("Expected exactly 2 arguments");
    }
    if(argv[1][0] == 'e') {
        std::vector<uint8_t> converted = base256::convert10to256(std::string(argv[2]));
        std::vector<uint8_t> encoded = lvt::encodeLength(converted);
        for(auto digit: encoded) {
            std::cout << HEX(digit);
        }
        std::cout << std::endl;
    }
    else if(argv[1][0] == 'd'){
        std::vector<uint8_t> converted = base256::convert16to256(std::string(argv[2]));
        std::vector<uint8_t> decoded = lvt::decodeLength(converted);
        std::string deconverted = base256::convert256to10(decoded);
        std::cout << deconverted << std::endl;
    }
    else {
        throw std::invalid_argument("First argument must be either 'e' or 'd'");
    }
    return 0;
}