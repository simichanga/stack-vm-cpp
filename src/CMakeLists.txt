# Specify the minimum version of CMake required
cmake_minimum_required(VERSION 3.25)

# Define the project name and language
project(StackVM LANGUAGES CXX)

# Set the C++ standard to C++23
set(CMAKE_CXX_STANDARD 23)

# Create a library from the source files
add_library(StackVM
        src/lexer.cpp
        src/vm.cpp
        src/parser.cpp
)

# Create the executable for the main program
add_executable(stack_vm src/main.cpp)

# Link the StackVM library with the executable
target_link_libraries(stack_vm PRIVATE StackVM)

# Include directories for the project (header files)
target_include_directories(StackVM PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_include_directories(stack_vm PRIVATE ${CMAKE_SOURCE_DIR}/include)

# Ensure that the linker uses C++23 or later
target_compile_features(stack_vm PRIVATE cxx_std_23)
