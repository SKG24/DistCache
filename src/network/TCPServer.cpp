// src/network/TCPServer.cpp
#include "TCPServer.h"

TCPServer::TCPServer(int port) : port(port) {}

void TCPServer::start() {
    std::cout << "[TCPServer] Listening on port " << port << " (simulation)\n";
}
