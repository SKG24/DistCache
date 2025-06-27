#pragma once
#include <unordered_map>
#include <list>
#include <string>
#include <mutex>
#include <shared_mutex>
#include <chrono>

class LRUCache {
public:
    LRUCache(size_t capacity);
    bool get(const std::string& key, std::string& value);
    void set(const std::string& key, const std::string& value, int ttl_seconds = -1);
    void del(const std::string& key);
    bool exists(const std::string& key);
    void cleanup_expired();

private:
    struct Entry {
        std::string value;
        std::chrono::steady_clock::time_point expire_time;
    };

    std::unordered_map<std::string, Entry> cache;
    std::list<std::string> lru;
    std::unordered_map<std::string, std::list<std::string>::iterator> lru_map;
    size_t capacity;
    mutable std::shared_mutex mtx;
};
