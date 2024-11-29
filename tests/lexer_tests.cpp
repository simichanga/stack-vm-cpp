#include "lexer.h"
#include <cassert>
#include <iostream>

int main() {
    Lexer lexer("2 + 3");
    auto tokens = lexer.tokenize();

    assert(tokens.size() == 3);
    assert(tokens[0].type == "NUMBER");
    assert(tokens[1].type == "PLUS");
    assert(tokens[2].type == "NUMBER");

    std::cout << "Lexer Tests Passed!" << std::endl;
    return 0;
}
