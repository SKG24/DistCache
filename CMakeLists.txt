cmake_minimum_required(VERSION 3.14)
project(DistCache)

set(CMAKE_CXX_STANDARD 17)

# -----------------------
# Core Application
# -----------------------
file(GLOB_RECURSE CORE_SOURCES
    src/storage/*.cpp
    src/network/*.cpp
    src/cluster/*.cpp
    src/monitoring/*.cpp
)

add_executable(distcache ${CORE_SOURCES} src/main.cpp)

# Include directories
include_directories(
    src/storage
    src/network
    src/cluster
    src/monitoring
)

# MessagePack (if needed)
find_package(PkgConfig REQUIRED)
pkg_check_modules(MSGPACK REQUIRED msgpack)
include_directories(${MSGPACK_INCLUDE_DIRS})
target_link_libraries(distcache ${MSGPACK_LIBRARIES})

# -----------------------
# Add Tests & Benchmarks
# -----------------------
enable_testing()
add_subdirectory(tests)
add_subdirectory(benchmark)
