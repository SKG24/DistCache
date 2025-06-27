// src/storage/MMapPersistence.h
#pragma once
#include <string>
#include <unordered_map>
#include <fstream>

class MMapPersistence {
public:
    explicit MMapPersistence(const std::string& file);

    void snapshot(const std::unordered_map<std::string, std::string>& data);
    std::unordered_map<std::string, std::string> load();

private:
    std::string file_name;
};
