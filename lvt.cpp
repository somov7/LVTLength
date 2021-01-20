//
// Created by catghoti on 19.01.2021.
//

#include <cstdint>
#include <cstddef>
#include <algorithm>
#include <cassert>
#include "lvt.h"

std::vector<uint8_t> lvt::encodeLength(const std::vector<uint8_t> &value) {
    assert(!value.empty());
    if (value.size() == 1 && value[0] <= maxShort) {
        return std::vector<uint8_t>(1, static_cast<uint8_t>(value.size()));
    }
    assert(value.size() < 127);
    std::vector<uint8_t> encoded(value.size() + 1);
    encoded[0] = (1 << 8) | value.size();
    std::copy(value.begin(), value.end(), encoded.begin() + 1);
    return encoded;
}

std::vector<uint8_t> lvt::decodeLength(const std::vector<uint8_t> &value) {
    return lvt::decodeLength(value.data());
}

std::vector<uint8_t> lvt::decodeLength(const uint8_t* value) {
    bool isShortForm = value[0] >> 7;
    if (isShortForm) {
        return std::vector<uint8_t>(1, value[0] & 0x7F);
    }
    size_t length = value[0] & 0x7F;
    std::vector<uint8_t> decoded(length);
    std::copy(&value[1], &value[length + 1], decoded.begin());
    return decoded;
}