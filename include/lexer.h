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

// Structure to hold token information
struct TokenInfo {
    Token type;   // The type of token (e.g., FUNC, VAR, IDENTIFIER)
    std::string value;  // The string representation of the token (e.g., function name)

    // Constructor to initialize TokenInfo with a type and value
    TokenInfo(Token t, const std::string& v) : type(t), value(v) {}

    // Getter function to return the value of the token
    std::string getValue() const { return value; }
};

// Function declarations
class Lexer {
public:
    std::vector<Token> tokenize(const std::string& source);
};

#endif // LEXER_H
