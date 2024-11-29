# Specify the minimum version of CMake
cmake_minimum_required(VERSION 3.14)

# Define the project name
project(StackVMTests LANGUAGES CXX)

# Set the C++ standard to C++23
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include StackVMLib (the main source files for lexer, parser, and vm)
add_library(StackVMLib STATIC
        ../src/lexer.cpp
        ../src/vm.cpp
        ../src/parser.cpp
)

# Include directories for StackVMLib (this makes sure all targets linking with this lib get the include paths)
target_include_directories(StackVMLib PUBLIC ${CMAKE_SOURCE_DIR}/../include)

# Fetch Google Test
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/heads/main.zip
)
# Download and make Google Test available
FetchContent_MakeAvailable(googletest)

# Create the test executable for lexer tests
add_executable(lexer_tests lexer_tests.cpp)
# Link Google Test and StackVMLib with lexer_tests
target_link_libraries(lexer_tests PRIVATE gtest gtest_main StackVMLib)
# Include directories for lexer_tests (adding include directory explicitly)
target_include_directories(lexer_tests PRIVATE ${CMAKE_SOURCE_DIR}/../include)

# Create the test executable for parser tests
add_executable(parser_tests parser_tests.cpp)
# Link Google Test and StackVMLib with parser_tests
target_link_libraries(parser_tests PRIVATE gtest gtest_main StackVMLib)
# Include directories for parser_tests (adding include directory explicitly)
target_include_directories(parser_tests PRIVATE ${CMAKE_SOURCE_DIR}/../include)

# Enable testing
enable_testing()

# Register both test executables to CTest
add_test(NAME LexerTests COMMAND lexer_tests)
add_test(NAME ParserTests COMMAND parser_tests)
