set(CORE_SOURCES
    ${CMAKE_SOURCE_DIR}/src/storage/LRUCache.cpp
    ${CMAKE_SOURCE_DIR}/src/storage/WAL.cpp
    ${CMAKE_SOURCE_DIR}/src/storage/MMapPersistence.cpp
    ${CMAKE_SOURCE_DIR}/src/storage/RESPParser.cpp
    ${CMAKE_SOURCE_DIR}/src/monitoring/MetricsCollector.cpp
)

add_executable(run_benchmark
    ${CMAKE_CURRENT_SOURCE_DIR}/benchmark.cpp
    ${CORE_SOURCES}
)

target_include_directories(run_benchmark PRIVATE ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(run_benchmark pthread)
