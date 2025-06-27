// tests/test_MetricsCollector.cpp
#include <gtest/gtest.h>
#include <thread> 
#include "monitoring/MetricsCollector.h"

TEST(MetricsCollectorTest, RecordAndGenerate) {
    MetricsCollector metrics;
    metrics.record_latency(15.5);
    metrics.increment_counter("test_ops");
    std::string json = metrics.generate_json();
    ASSERT_NE(json.find("latency"), std::string::npos);
}
