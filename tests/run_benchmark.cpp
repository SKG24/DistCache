#include <iostream>
#include <chrono>
#include <threads>
#include "../src/storage/LRUCache.h"
#include "../src/storage/WAL.h"
#include "../src/monitoring/MetricsCollector.h"

void benchmarkLRUCache() {
    std::cout << "[Benchmark] LRUCache Set/Get\n";
    LRUCache cache(1000);
    const int iterations = 100000;
    
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < iterations; ++i) {
        cache.set("key" + std::to_string(i), "value" + std::to_string(i));
    }
    auto mid = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < iterations; ++i) {
        std::string value;
        cache.get("key" + std::to_string(i), value);
    }
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> set_time = mid - start;
    std::chrono::duration<double> get_time = end - mid;

    std::cout << "Set time: " << set_time.count() << "s\n";
    std::cout << "Get time: " << get_time.count() << "s\n";
}

void benchmarkWAL() {
    std::cout << "\n[Benchmark] WAL Append\n";
    WAL wal("benchmark_wal.log");

    const int operations = 50000;
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < operations; ++i) {
        wal.append("SET", "key" + std::to_string(i), "value" + std::to_string(i));
    }
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> append_time = end - start;
    std::cout << "Append " << operations << " entries in " << append_time.count() << "s\n";
}

void benchmarkMetricsCollector() {
    std::cout << "\n[Benchmark] MetricsCollector\n";
    const int ops = 100000;

    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < ops; ++i) {
        MetricsCollector::record_latency(1.0 + i % 100);
        MetricsCollector::increment_counter("test_ops");
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    std::cout << "Recorded " << ops << " ops in " << duration.count() << "s\n";
}

int main() {
    benchmarkLRUCache();
    benchmarkWAL();
    benchmarkMetricsCollector();
    return 0;
}
