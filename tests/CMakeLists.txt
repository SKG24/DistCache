enable_testing()

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/release-1.12.1.zip
)
FetchContent_MakeAvailable(googletest)

# Test source files
file(GLOB TEST_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
)

# Core files for linking
set(CORE_SOURCES
    ${CMAKE_SOURCE_DIR}/src/storage/LRUCache.cpp
    ${CMAKE_SOURCE_DIR}/src/storage/WAL.cpp
    ${CMAKE_SOURCE_DIR}/src/storage/MMapPersistence.cpp
    ${CMAKE_SOURCE_DIR}/src/storage/RESPParser.cpp
    ${CMAKE_SOURCE_DIR}/src/monitoring/MetricsCollector.cpp
)

add_executable(run_tests
    ${TEST_SOURCES}
    ${CORE_SOURCES}
)

target_include_directories(run_tests PRIVATE ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(run_tests gtest gtest_main pthread)

include(GoogleTest)
gtest_discover_tests(run_tests)
