// lexer.h
#ifndef LEXER_H
#define LEXER_H

#include <vector>
#include <string>
#include <unordered_map>

// Define Token enum here
enum class Token {
    FUNC,
    VAR,
    RETURN,
    IDENTIFIER,
    NUMBER,
    LEFT_PAREN,
    RIGHT_PAREN,
    COMMA,
    PLUS,
    END,
    INVALID
};

// Function declarations
class Lexer {
public:
    std::vector<Token> tokenize(const std::string& source);
};

#endif // LEXER_H
