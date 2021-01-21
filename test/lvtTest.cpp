//
// Created by catghoti on 21.01.2021.
//

#include <gtest/gtest.h>
#include "../src/lvt.h"

TEST(LVTEncoder, ThrowsExceptions) {
    std::vector<uint8_t> argument;
    argument = std::vector<uint8_t>(127, 0x00); // 2^1008
    argument[0] = 0x01;
    ASSERT_THROW(lvt::encodeLength(argument), std::invalid_argument);

    argument = std::vector<uint8_t>(0);
    ASSERT_THROW(lvt::encodeLength(argument), std::invalid_argument);

    argument = std::vector<uint8_t>(1, 0x00);
    ASSERT_THROW(lvt::encodeLength(argument), std::invalid_argument);

}

TEST(LVTEncoder, EncodedValuesAreCorrect) {
    std::vector<uint8_t> expected, argument;

    expected = std::vector<uint8_t>{0x01}; // 1
    argument = std::vector<uint8_t>{0x01};
    ASSERT_EQ(expected, lvt::encodeLength(argument));

    expected = std::vector<uint8_t>{0x7F}; // 127
    argument = std::vector<uint8_t>{0x7F};
    ASSERT_EQ(expected, lvt::encodeLength(argument));

    expected = std::vector<uint8_t>{0x81, 0x80}; // 128
    argument = std::vector<uint8_t>{0x80};
    ASSERT_EQ(expected, lvt::encodeLength(argument));

    expected = std::vector<uint8_t>{0x84, 0x49, 0x96, 0x02, 0xD2}; // 1234567890
    argument = std::vector<uint8_t>{0x49, 0x96, 0x02, 0xD2};
    ASSERT_EQ(expected, lvt::encodeLength(argument));

    expected = std::vector<uint8_t>(127, 0xFF); // 2^1008 - 1
    expected[0] = 0xFE;
    argument = std::vector<uint8_t>(126, 0xFF);
    ASSERT_EQ(expected, lvt::encodeLength(argument));
}

TEST(LVTDecoder, ThrowsExceptions) {
    std::vector<uint8_t> argument;
    argument = std::vector<uint8_t>(1, 0x00); // 0
    ASSERT_THROW(lvt::decodeLength(argument), std::invalid_argument);

    argument = std::vector<uint8_t>(1, 0x80); // 0
    ASSERT_THROW(lvt::decodeLength(argument), std::invalid_argument);

    argument = std::vector<uint8_t>(128, 0x00); // 2^1008
    argument[0] = 0xFF;
    argument[1] = 0x01;
    ASSERT_THROW(lvt::decodeLength(argument), std::invalid_argument);
}

TEST(LVTDecoder, EncodedValuesAreCorrect) {
    std::vector<uint8_t> expected, argument;

    expected = std::vector<uint8_t>{0x01}; // 1
    argument = std::vector<uint8_t>{0x01};
    ASSERT_EQ(expected, lvt::decodeLength(argument));

    expected = std::vector<uint8_t>{0x7F}; // 127
    argument = std::vector<uint8_t>{0x7F};
    ASSERT_EQ(expected, lvt::decodeLength(argument));

    expected = std::vector<uint8_t>{0x80}; // 128
    argument = std::vector<uint8_t>{0x81, 0x80};
    ASSERT_EQ(expected, lvt::decodeLength(argument));

    expected = std::vector<uint8_t>{0x49, 0x96, 0x02, 0xD2}; // 1234567890
    argument = std::vector<uint8_t>{0x84, 0x49, 0x96, 0x02, 0xD2};
    ASSERT_EQ(expected, lvt::decodeLength(argument));

    expected = std::vector<uint8_t>(126, 0xFF); // 2^1008 - 1
    argument = std::vector<uint8_t>(127, 0xFF);
    argument[0] = 0xFE;
    ASSERT_EQ(expected, lvt::decodeLength(argument));
}