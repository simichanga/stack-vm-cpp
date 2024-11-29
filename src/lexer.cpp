#include "lexer.h"
#include <cctype>

std::vector<Token> Lexer::tokenize(const std::string& source) {
    std::vector<Token> tokens;
    size_t i = 0;

    while (i < source.length()) {
        char c = source[i];

        if (std::isspace(c)) {
            // Skip whitespace
            i++;
            continue;
        }

        if (std::isdigit(c)) {
            // Handle numbers
            tokens.push_back(Token::NUMBER);
            while (i < source.length() && std::isdigit(source[i])) {
                i++; // Consume entire number
            }
        } else if (c == '+') {
            tokens.push_back(Token::PLUS);
            i++;
        } else if (c == '(') {
            tokens.push_back(Token::LEFT_PAREN);
            i++;
        } else if (c == ')') {
            tokens.push_back(Token::RIGHT_PAREN);
            i++;
        } else if (c == ',') {
            tokens.push_back(Token::COMMA);
            i++;
        } else if (std::isalpha(c)) {
            // Handle identifiers and keywords
            std::string identifier;
            while (i < source.length() && (std::isalnum(source[i]) || source[i] == '_')) {
                identifier += source[i];
                i++;
            }
            if (identifier == "func") {
                tokens.push_back(Token::FUNC);
            } else if (identifier == "return") {
                tokens.push_back(Token::RETURN);
            } else {
                tokens.push_back(Token::IDENTIFIER);
            }
        } else {
            // Invalid character
            tokens.push_back(Token::INVALID);
            i++;
        }
    }

    tokens.push_back(Token::END);
    return tokens;
}
