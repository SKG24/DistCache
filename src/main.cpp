#include <iostream>
#include <thread>
#include <chrono>
#include "storage/LRUCache.h"
#include "storage/WAL.h"
#include "storage/MMapPersistence.h"
#include "storage/RESPParser.h"
#include "network/TCPServer.h"
#include "cluster/NodeDiscovery.h"
#include "monitoring/HttpDashboard.h"
#include "monitoring/MetricsCollector.h"

int main() {
    std::cout << "[DistCache] Initializing core components...\n";
    LRUCache cache(10000);
    WAL wal("wal.log");
    MMapPersistence persistence("snapshot.dat");
    RESPParser parser;
    MetricsCollector metrics;

    auto persisted_data = persistence.load();
    for (const auto& [key, val] : persisted_data) {
        cache.set(key, val);
    }
    for (auto [op, key, val] : wal.replay()) {
        if (op == "SET") cache.set(key, val);
        else if (op == "DEL") cache.del(key);
    }

    std::cout << "[DistCache] Starting TCP server on port 6379...\n";
    TCPServer server(6379);
    std::thread server_thread([&]() { server.start(); });

    std::cout << "[DistCache] Launching node discovery...\n";
    NodeDiscovery discovery;
    std::thread discovery_thread([&]() {
        discovery.broadcast_heartbeat();
        discovery.listen_for_heartbeats();
    });

    std::cout << "[DistCache] Starting metrics dashboard on port 8080...\n";
    HttpDashboard dashboard;
    std::thread dashboard_thread([&]() { dashboard.start(8080); });

    std::thread cleanup_thread([&]() {
        while (true) {
            std::this_thread::sleep_for(std::chrono::seconds(5));
            cache.cleanup_expired();
        }
    });

    std::cout << "[DistCache] System is up and running. Press Ctrl+C to stop.\n";
    server_thread.join();
    discovery_thread.join();
    dashboard_thread.join();
    cleanup_thread.join();

    return 0;
}
