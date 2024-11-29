#include "lexer.h"
#include <cassert>
#include <iostream>

std::string tokenToString(Token token) {
    switch (token) {
        case Token::FUNC: return "FUNC";
        case Token::VAR: return "VAR";
        case Token::RETURN: return "RETURN";
        case Token::IDENTIFIER: return "IDENTIFIER";
        case Token::NUMBER: return "NUMBER";
        case Token::LEFT_PAREN: return "LEFT_PAREN";
        case Token::RIGHT_PAREN: return "RIGHT_PAREN";
        case Token::COMMA: return "COMMA";
        case Token::PLUS: return "PLUS";
        case Token::END: return "END";
        case Token::INVALID: return "INVALID";
        default: return "UNKNOWN";
    }
}

void testLexer() {
    Lexer lexer;

    // Test input string
    std::string input = "2 + 3";

    // Expected tokens
    std::vector<Token> expectedTokens = {
        Token::NUMBER, Token::PLUS, Token::NUMBER, Token::END
    };

    // Tokenize the input
    auto tokens = lexer.tokenize(input);

    // Check token count
    assert(tokens.size() == expectedTokens.size() && "Token count mismatch");

    // Check each token
    for (size_t i = 0; i < tokens.size(); ++i) {
        assert(tokens[i] == expectedTokens[i] &&
               ("Token mismatch at position " + std::to_string(i) +
                ": expected " + tokenToString(expectedTokens[i]) +
                ", got " + tokenToString(tokens[i])).c_str());
    }

    std::cout << "Lexer Tests Passed!" << std::endl;
}

int main() {
    try {
        testLexer();
    } catch (const std::exception& e) {
        std::cerr << "Test failed: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
