// tests/test_RESPParser.cpp
#include <gtest/gtest.h>
#include <thread> 
#include "storage/RESPParser.h"

TEST(RESPParserTest, ParseBasicCommand) {
    RESPParser parser;
    auto [cmd, args] = parser.parse("mykey");
    ASSERT_EQ(cmd, "GET");
    ASSERT_EQ(args.size(), 1);
    ASSERT_EQ(args[0], "mykey");
}

TEST(RESPParserTest, SerializeResponse) {
    RESPParser parser;
    std::string serialized = parser.serialize("OK");
    ASSERT_EQ(serialized, "+OK\r\n");
}
