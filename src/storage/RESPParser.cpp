// src/network/RESPParser.cpp
#include "RESPParser.h"

std::tuple<std::string, std::vector<std::string>> RESPParser::parse(const std::string& raw) {
    // Basic parser mockup for demonstration
    return {"GET", {raw}};
}

std::string RESPParser::serialize(const std::string& result) {
    return "+" + result + "\r\n";
}
