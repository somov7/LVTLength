//
// Created by catghoti on 20.01.2021.
//

#ifndef LVT_BASE256_H
#define LVT_BASE256_H

namespace base256 {
    std::vector<uint8_t> convert10to256(std::string number);
    std::vector<uint8_t> convert16to256(std::string number);
    std::string convert256to10(std::vector<uint8_t> number);
}

#endif //LVT_BASE256_H
