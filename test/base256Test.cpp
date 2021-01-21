//
// Created by catghoti on 21.01.2021.
//

#include <gtest/gtest.h>
#include "../src/base256.h"

TEST(convert10to256, ThrowsException) {
    ASSERT_THROW(base256::convert10to256("A"), std::invalid_argument);
}

TEST(convert10to256, EqualsExpected) {
    std::vector<uint8_t> expected;

    expected = std::vector<uint8_t>{0x00}; // 0
    ASSERT_EQ(expected, base256::convert10to256("0"));

    expected = std::vector<uint8_t>{0x01}; // 1
    ASSERT_EQ(expected, base256::convert10to256("1"));

    expected = std::vector<uint8_t>{0x7F}; // 127
    ASSERT_EQ(expected, base256::convert10to256("127"));

    expected = std::vector<uint8_t>{0x80}; // 128
    ASSERT_EQ(expected, base256::convert10to256("128"));

    expected = std::vector<uint8_t>{0x49, 0x96, 0x02, 0xD2}; // 1234567890
    ASSERT_EQ(expected, base256::convert10to256("1234567890"));

    expected = std::vector<uint8_t>(126, 0xFF); // 2^1008 - 1
    ASSERT_EQ(expected,
              base256::convert10to256("2743062034396844341627968125593604635037196317966166035056000994228098690879836473582587849768181396806642362668936055872479091931372323951612051859122835149807249350355003132267795098895967012320756270631179897595796976964454084495146379250195728106130226298287754794921070036903071843030324651025760255")
              );
}

TEST(convert256to10, EqualsExpected) {
    std::vector<uint8_t> argument;

    argument = std::vector<uint8_t>{0x00}; // 0
    ASSERT_EQ("0", base256::convert256to10(argument));

    argument = std::vector<uint8_t>{0x01}; // 1
    ASSERT_EQ("1", base256::convert256to10(argument));

    argument = std::vector<uint8_t>{0x7F}; // 127
    ASSERT_EQ("127", base256::convert256to10(argument));

    argument = std::vector<uint8_t>{0x80}; // 128
    ASSERT_EQ("128", base256::convert256to10(argument));

    argument = std::vector<uint8_t>{0x49, 0x96, 0x02, 0xD2}; // 1234567890
    ASSERT_EQ("1234567890", base256::convert256to10(argument));

    argument = std::vector<uint8_t>(126, 0xFF); // 2^1008 - 1
    ASSERT_EQ("2743062034396844341627968125593604635037196317966166035056000994228098690879836473582587849768181396806642362668936055872479091931372323951612051859122835149807249350355003132267795098895967012320756270631179897595796976964454084495146379250195728106130226298287754794921070036903071843030324651025760255",
              base256::convert256to10(argument)
              );
}

TEST(convert16to256, ThrowsException) {
    ASSERT_THROW(base256::convert16to256("GH"), std::invalid_argument);
}

TEST(convert16to256, EqualsExpected) {
    std::vector<uint8_t> expected;

    expected = std::vector<uint8_t>{0x00}; // 0
    ASSERT_EQ(expected, base256::convert16to256("0"));

    expected = std::vector<uint8_t>{0x01}; // 1
    ASSERT_EQ(expected, base256::convert16to256("1"));

    expected = std::vector<uint8_t>{0x7F}; // 127
    ASSERT_EQ(expected, base256::convert16to256("7F"));

    expected = std::vector<uint8_t>{0x80}; // 128
    ASSERT_EQ(expected, base256::convert16to256("80"));

    expected = std::vector<uint8_t>{0x49, 0x96, 0x02, 0xD2}; // 1234567890
    ASSERT_EQ(expected, base256::convert16to256("499602D2"));

    expected = std::vector<uint8_t>(126, 0xFF); // 2^1008 - 1
    ASSERT_EQ(expected,
              base256::convert16to256("FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF")
    );
}