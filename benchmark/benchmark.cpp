// benchmarks/benchmark.cpp
#include <iostream>
#include <chrono>
#include <thread>
#include <vector>
#include <random>
#include "storage/LRUCache.h"
#include "storage/WAL.h"
#include "storage/MMapPersistence.h"
#include "monitoring/MetricsCollector.h"

void run_benchmark(LRUCache& cache, MetricsCollector& metrics, int num_ops) {
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < num_ops; ++i) {
        std::string key = "key" + std::to_string(i);
        std::string value = "value" + std::to_string(i);
        cache.set(key, value);
    }
    auto end = std::chrono::high_resolution_clock::now();
    double duration = std::chrono::duration<double>(end - start).count();
    double throughput = num_ops / duration;
    std::cout << "[Benchmark] SET throughput: " << throughput << " ops/sec\n";
    metrics.record_latency(duration * 1000);
}

void run_get_benchmark(LRUCache& cache, MetricsCollector& metrics, int num_ops) {
    std::default_random_engine rng;
    std::uniform_int_distribution<int> dist(0, num_ops - 1);

    auto start = std::chrono::high_resolution_clock::now();
    int hits = 0;
    for (int i = 0; i < num_ops; ++i) {
        std::string key = "key" + std::to_string(dist(rng));
        std::string val;
        if (cache.get(key, val)) hits++;
    }
    auto end = std::chrono::high_resolution_clock::now();
    double duration = std::chrono::duration<double>(end - start).count();
    double throughput = num_ops / duration;
    std::cout << "[Benchmark] GET throughput: " << throughput << " ops/sec | Hits: " << hits << "\n";
    metrics.record_latency(duration * 1000);
}

int main() {
    std::cout << "[Benchmark] Initializing...\n";
    LRUCache cache(100000);
    MetricsCollector metrics;

    run_benchmark(cache, metrics, 100000);
    run_get_benchmark(cache, metrics, 50000);

    std::cout << "[Benchmark] JSON Report: " << metrics.generate_json() << "\n";
    return 0;
}
