cmake_minimum_required(VERSION 3.12) # You can adjust the minimum required version as needed
project(SeqIO)

# Set the C++ standard to use (e.g., C++11, C++14, C++17)
set(CMAKE_CXX_STANDARD 17)

# Add your source files and header files
set(SOURCES
    tests/benchmark_io.cpp
)

# Add the Google Test library
find_package(GTest REQUIRED)
find_package(ZLIB REQUIRED)

# Create an executable for your project
add_executable(tests ${SOURCES})

# Link the executable with the Google Test library
target_link_libraries(tests GTest::GTest GTest::Main ZLIB::ZLIB)

# Include the directory with your header files
target_include_directories(tests PRIVATE include)

# target_compile_options(tests PRIVATE -Wall -Wextra)
