#include <gtest/gtest.h>
#include <fstream>
#include <thread> 
#include "storage/WAL.h"

TEST(WALTest, AppendAndReplay) {
    std::remove("wal_test.log");  // Ensure clean state

    WAL wal("wal_test.log");
    wal.append("SET", "key1", "value1");
    wal.append("DEL", "key2");

    auto ops = wal.replay();
    ASSERT_EQ(ops.size(), 2);
    EXPECT_EQ(std::get<0>(ops[0]), "SET");
    EXPECT_EQ(std::get<1>(ops[0]), "key1");
    EXPECT_EQ(std::get<2>(ops[0]), "value1");

    EXPECT_EQ(std::get<0>(ops[1]), "DEL");
    EXPECT_EQ(std::get<1>(ops[1]), "key2");
}
