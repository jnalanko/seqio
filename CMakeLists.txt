cmake_minimum_required(VERSION 3.12) # You can adjust the minimum required version as needed
project(SeqIO)

# Set the C++ standard to use (e.g., C++11, C++14, C++17)
set(CMAKE_CXX_STANDARD 17)

# Add your source files and header files
set(SOURCES
    tests/benchmark_io.cpp tests/common.cpp
)

# Add the Google Test library

find_package(ZLIB REQUIRED)

if(BUILD_SEQIO_BENCHMARK)
    # Create benchmark executable
    add_executable(benchmark ${SOURCES})

    # Link the executable with the Google Test library
    target_link_libraries(benchmark ZLIB::ZLIB)

    # Include the directory with your header files
    target_include_directories(benchmark PRIVATE include)

    target_compile_options(benchmark PRIVATE -Wall -Wextra -O3)
endif()

if(BUILD_SEQIO_TESTS)

    # Create a test executable and link with Google Test library
    find_package(GTest REQUIRED)
    add_executable(tests tests/test_IO.cpp tests/test_seqio.cpp tests/common.cpp)
    target_link_libraries(tests GTest::GTest GTest::Main ZLIB::ZLIB)

    # Include the directory with your header files for tests
    target_include_directories(tests PRIVATE include)

endif()