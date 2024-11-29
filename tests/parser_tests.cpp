#include "../../stack-vm-cpp/include/lexer.h"
#include "../../stack-vm-cpp/src/parser.cpp"
#include <iostream>
#include <vector>
#include <cassert>

// Helper function to tokenize a string
std::vector<Token> tokenize(const std::string& input) {
    Lexer lexer;
    return lexer.tokenize(input);
}

void testFunctionParsing() {
    Parser parser;

    // Test case 1: Simple function without parameters and return
    std::string source = "func foo() return";
    std::vector<Token> tokens = tokenize(source);
    parser.parse(tokens);

    // Assert function foo was parsed correctly
    assert(parser.functionTable.find("foo") != parser.functionTable.end());
    assert(parser.functionTable["foo"].parameters.empty());
    assert(parser.functionTable["foo"].instructions.size() == 1);
    assert(parser.functionTable["foo"].instructions[0] == "RETURN");

    std::cout << "testFunctionParsing passed!" << std::endl;
}

void testFunctionWithParameters() {
    Parser parser;

    // Test case 2: Function with parameters
    std::string source = "func bar(x) return";
    std::vector<Token> tokens = tokenize(source);
    parser.parse(tokens);

    // Assert function bar was parsed correctly with parameters
    assert(parser.functionTable.find("bar") != parser.functionTable.end());
    assert(parser.functionTable["bar"].parameters.size() == 1);
    assert(parser.functionTable["bar"].parameters[0] == "x");
    assert(parser.functionTable["bar"].instructions.size() == 1);
    assert(parser.functionTable["bar"].instructions[0] == "RETURN");

    std::cout << "testFunctionWithParameters passed!" << std::endl;
}

void testInvalidFunction() {
    Parser parser;

    // Test case 3: Invalid function (missing return)
    std::string source = "func invalid(x)";
    std::vector<Token> tokens = tokenize(source);
    parser.parse(tokens);

    // Since there is no return, we expect no instructions
    assert(parser.functionTable.find("invalid") != parser.functionTable.end());
    assert(parser.functionTable["invalid"].instructions.empty());

    std::cout << "testInvalidFunction passed!" << std::endl;
}

int main() {
    testFunctionParsing();
    testFunctionWithParameters();
    testInvalidFunction();

    std::cout << "All tests passed!" << std::endl;

    return 0;
}
