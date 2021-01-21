//
// Created by catghoti on 19.01.2021.
//

#ifndef LVT_LVT_H
#define LVT_LVT_H

namespace lvt {
    const uint8_t maxShort = (1 << 7) - 1;

    std::vector<uint8_t> encodeLength(const std::vector<uint8_t> &value);

    std::vector<uint8_t> decodeLength(const std::vector<uint8_t> &value);
    std::vector<uint8_t> decodeLength(const uint8_t *value);
}
#endif //LVT_LVT_H
