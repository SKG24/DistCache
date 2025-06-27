# src/CMakeLists.txt

# Recursively find all .cpp files in src/
file(GLOB_RECURSE SRC_FILES *.cpp)

# Create the main executable target
add_executable(distcache ${SRC_FILES})

# Include header directories for internal includes
target_include_directories(distcache PRIVATE
    ${CMAKE_SOURCE_DIR}/src
)

# Link additional system libraries if needed
target_link_libraries(distcache
    pthread
)
