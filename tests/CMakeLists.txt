# Add the test executables for lexer, parser, and vm tests
add_executable(lexer_tests lexer_tests.cpp)
#add_executable(parser_tests parser_tests.cpp)
#add_executable(vm_tests vm_tests.cpp)

# Link the StackVM library with the test executables
target_link_libraries(lexer_tests PRIVATE StackVM)
#target_link_libraries(parser_tests PRIVATE StackVM)
#target_link_libraries(vm_tests PRIVATE StackVM)

# Include directories for the tests
target_include_directories(lexer_tests PRIVATE ${CMAKE_SOURCE_DIR}/include)
#target_include_directories(parser_tests PRIVATE ${CMAKE_SOURCE_DIR}/include)
#target_include_directories(vm_tests PRIVATE ${CMAKE_SOURCE_DIR}/include)
