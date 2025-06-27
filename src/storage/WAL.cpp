#include "WAL.h"

WAL::WAL(const std::string& filename) {
    wal_file.open(filename, std::ios::app);
}

void WAL::append(const std::string& operation, const std::string& key, const std::string& value) {
    std::lock_guard<std::mutex> lock(wal_mutex);
    wal_file << operation << " " << key << " " << value << "\n";
    wal_file.flush();
}

void WAL::append_binary(const std::string& op, const std::string& key, const std::string& value) {
    std::stringstream buffer;
    msgpack::pack(buffer, std::make_tuple(op, key, value));
    std::string data = buffer.str();
    wal_file.write(data.data(), data.size());
}

std::vector<std::tuple<std::string, std::string, std::string>> WAL::replay() {
    std::ifstream in("wal.log");
    std::vector<std::tuple<std::string, std::string, std::string>> ops;
    std::string op, key, value;
    while (in >> op >> key >> value) {
        ops.emplace_back(op, key, value);
    }
    return ops;
}
