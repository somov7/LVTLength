//
// Created by catghoti on 19.01.2021.
//

#include <cstdint>
#include <cstddef>
#include <algorithm>
#include <stdexcept>
#include "lvt.h"

std::vector<uint8_t> lvt::encodeLength(const std::vector<uint8_t> &value) {
    if (value.empty()) {
        throw std::invalid_argument("Value vector can not be empty");
    }
    if (value.size() >= 127) {
        throw std::invalid_argument("Value vector can not exceed 126 bytes");
    }
    if (value[0] == 0x00) {
        throw std::invalid_argument("Value must have non-zero length");
    }
    if (value.size() == 1 && value[0] <= maxShort) {
        return std::vector<uint8_t>(1, static_cast<uint8_t>(value[0]));
    }
    std::vector<uint8_t> encoded(value.size() + 1);
    encoded[0] = (1 << 7) | value.size();
    std::copy(value.begin(), value.end(), encoded.begin() + 1);
    return encoded;
}

std::vector<uint8_t> lvt::decodeLength(const std::vector<uint8_t> &value) {
    return lvt::decodeLength(value.data());
}

std::vector<uint8_t> lvt::decodeLength(const uint8_t *value) {
    if((value[0] & 0x7F) == 0) {
        throw std::invalid_argument("Value length must be positive");
    }
    if(value[0] == 0xFF) {
        throw std::invalid_argument("Value length must not exceed 126");
    }
    size_t length = value[0] & 0x7F;
    bool isShortForm = !(value[0] >> 7);
    if (isShortForm) {
        return std::vector<uint8_t>(1, length);
    }
    std::vector<uint8_t> decoded(length);
    std::copy(&value[1], &value[length + 1], decoded.begin());
    return decoded;
}