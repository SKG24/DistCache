// src/storage/LRUCache.cpp
#include "LRUCache.h"

LRUCache::LRUCache(size_t capacity) : capacity(capacity) {}

bool LRUCache::get(const std::string& key, std::string& value) {
    std::shared_lock lock(mtx);
    auto it = cache.find(key);
    if (it == cache.end()) return false;
    if (it->second.expire_time < std::chrono::steady_clock::now()) return false;
    value = it->second.value;
    return true;
}

void LRUCache::set(const std::string& key, const std::string& value, int ttl_seconds) {
    std::unique_lock lock(mtx);
    auto now = std::chrono::steady_clock::now();
    Entry e{value, ttl_seconds > 0 ? now + std::chrono::seconds(ttl_seconds) : now + std::chrono::hours(24)};
    cache[key] = e;
    if (lru_map.count(key)) lru.erase(lru_map[key]);
    lru.push_front(key);
    lru_map[key] = lru.begin();
    if (cache.size() > capacity) {
        std::string old_key = lru.back();
        lru.pop_back();
        cache.erase(old_key);
        lru_map.erase(old_key);
    }
}

void LRUCache::del(const std::string& key) {
    std::unique_lock lock(mtx);
    if (cache.count(key)) {
        cache.erase(key);
        lru.erase(lru_map[key]);
        lru_map.erase(key);
    }
}

bool LRUCache::exists(const std::string& key) {
    std::shared_lock lock(mtx);
    return cache.count(key);
}

void LRUCache::cleanup_expired() {
    std::unique_lock lock(mtx);
    auto now = std::chrono::steady_clock::now();
    for (auto it = cache.begin(); it != cache.end();) {
        if (it->second.expire_time < now) {
            lru.erase(lru_map[it->first]);
            lru_map.erase(it->first);
            it = cache.erase(it);
        } else {
            ++it;
        }
    }
}
