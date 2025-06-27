#pragma once
#include <iostream>
#include <string>

class MetricsCollector {
public:
    void record_latency(double ms);
    void increment_counter(const std::string& name);
    std::string generate_json();
};
