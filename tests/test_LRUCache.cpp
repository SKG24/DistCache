#include <gtest/gtest.h>
#include <thread>
#include "storage/LRUCache.h"

TEST(LRUCacheTest, BasicSetAndGet) {
    LRUCache cache(5);
    cache.set("key1", "value1");
    std::string value;
    bool found = cache.get("key1", value);
    EXPECT_TRUE(found);
    EXPECT_EQ(value, "value1");
}

TEST(LRUCacheTest, ExpirationTest) {
    LRUCache cache(5);
    cache.set("temp", "shortlived", 1);  // TTL: 1 sec
    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::string value;
    EXPECT_FALSE(cache.get("temp", value));
}

TEST(LRUCacheTest, EvictionTest) {
    LRUCache cache(2);
    cache.set("a", "1");
    cache.set("b", "2");
    cache.set("c", "3"); // should evict "a"

    std::string value;
    EXPECT_FALSE(cache.get("a", value));
    EXPECT_TRUE(cache.get("b", value));
    EXPECT_TRUE(cache.get("c", value));
}
