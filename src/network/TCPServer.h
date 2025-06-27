// src/network/TCPServer.h
#pragma once
#include <iostream>

class TCPServer {
public:
    explicit TCPServer(int port);
    void start();

private:
    int port;
};
