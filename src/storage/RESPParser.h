// src/network/RESPParser.h
#pragma once
#include <string>
#include <vector>
#include <tuple>

class RESPParser {
public:
    std::tuple<std::string, std::vector<std::string>> parse(const std::string& raw);
    std::string serialize(const std::string& result);
};
