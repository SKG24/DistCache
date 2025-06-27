// src/storage/MMapPersistence.cpp
#include "MMapPersistence.h"

MMapPersistence::MMapPersistence(const std::string& file) : file_name(file) {}

void MMapPersistence::snapshot(const std::unordered_map<std::string, std::string>& data) {
    std::ofstream out(file_name);
    for (const auto& [k, v] : data) {
        out << k << " " << v << "\n";
    }
}

std::unordered_map<std::string, std::string> MMapPersistence::load() {
    std::ifstream in(file_name);
    std::unordered_map<std::string, std::string> data;
    std::string key, value;
    while (in >> key >> value) {
        data[key] = value;
    }
    return data;
}
