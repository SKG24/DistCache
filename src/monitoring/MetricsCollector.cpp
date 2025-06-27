// src/monitoring/MetricsCollector.cpp
#include "MetricsCollector.h"

void MetricsCollector::record_latency(double ms) {
    std::cout << "Latency: " << ms << "ms\n";
}

void MetricsCollector::increment_counter(const std::string& name) {
    std::cout << "Counter: " << name << " incremented\n";
}

std::string MetricsCollector::generate_json() {
    return "{\"latency\":5.5}";
}
