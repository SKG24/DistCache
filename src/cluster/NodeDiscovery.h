// src/cluster/NodeDiscovery.h
#pragma once
#include <iostream>

class NodeDiscovery {
public:
    void broadcast_heartbeat();
    void listen_for_heartbeats();
};
