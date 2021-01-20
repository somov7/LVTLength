//
// Created by catghoti on 20.01.2021.
//

#include <cstdint>
#include <string>
#include <vector>
#include <algorithm>
#include <cassert>
#include "base256.h"

uint8_t charToHex(char c) {
    assert(isxdigit(c));
    if(c >= '0' && c <= '9') {
        return c - '0';
    }
    if(c >= 'A' && c <= 'F') {
        return c - 'A' + 10;
    }
    return c - 'a' + 10;
}

std::vector<uint8_t> base256::convert10to256(std::string number) {
    std::vector<uint8_t> digits;
    assert(std::all_of(number.begin(), number.end(), ::isdigit));
    while (!number.empty()) {
        std::string newNumber;
        uint32_t remainder = 0;
        for (char digit : number) {
            digit -= '0';
            remainder = remainder * 10 + digit;
            if (remainder < 256) {
                if (!newNumber.empty()) {
                    newNumber += '0';
                }
            } else {
                uint32_t newDigit = remainder / 256;
                remainder %= 256;
                newNumber += newDigit + '0';
            }
        }
        number = std::move(newNumber);
        digits.push_back(static_cast<uint8_t>(remainder));
    }
    std::reverse(digits.begin(), digits.end());
    return digits;
}

std::vector<uint8_t> base256::convert16to256(std::string number) {
    std::vector<uint8_t> digits;
    if(number.length() & 1) {
        digits.push_back(charToHex(number[0]));
    }
    for(int i = number.length() & 1; i < number.size(); i += 2) {
        digits.push_back(charToHex(number[i]) * 16 + charToHex(number[i + 1]));
    }
    return digits;
}

std::string base256::convert256to10(std::vector<uint8_t> number) {
    std::string digits;
    while(!number.empty()) {
        std::vector<uint8_t> newNumber;
        uint32_t remainder = 0;
        for(uint8_t digit : number) {
            remainder = remainder * 256 + digit;
            if (remainder < 10) {
                if (!newNumber.empty()) {
                    newNumber.push_back(0);
                }
            } else {
                uint32_t newDigit = remainder / 10;
                remainder %= 10;
                newNumber.push_back(newDigit);
            }
        }
        number = std::move(newNumber);
        digits.push_back(static_cast<uint8_t>(remainder + '0'));
    }
    std::reverse(digits.begin(), digits.end());
    return digits;
}

