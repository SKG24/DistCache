// tests/test_MMapPersistence.cpp
#include <gtest/gtest.h>
#include <thread> 
#include "storage/MMapPersistence.h"
#include <fstream>

TEST(MMapPersistenceTest, SnapshotAndLoad) {
    std::string file = "test_snapshot.dat";
    std::unordered_map<std::string, std::string> data = {
        {"key1", "value1"},
        {"key2", "value2"}
    };

    MMapPersistence persist(file);
    persist.snapshot(data);

    auto loaded = persist.load();
    ASSERT_EQ(loaded.size(), 2);
    ASSERT_EQ(loaded["key1"], "value1");
    ASSERT_EQ(loaded["key2"], "value2");

    std::remove(file.c_str());
}
