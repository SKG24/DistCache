// src/storage/WAL.h
#pragma once
#include <string>
#include <vector>
#include <tuple>
#include <mutex>
#include <fstream>
#include <sstream>
#include <msgpack.hpp>

class WAL {
public:
    explicit WAL(const std::string& filename);

    void append(const std::string& operation, const std::string& key, const std::string& value = "");
    void append_binary(const std::string& operation, const std::string& key, const std::string& value = "");

    std::vector<std::tuple<std::string, std::string, std::string>> replay();

private:
    std::ofstream wal_file;
    std::mutex wal_mutex;
};
