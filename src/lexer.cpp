// lexer.cpp
#include "lexer.h"
#include <sstream>

std::vector<Token> Lexer::tokenize(const std::string& source) {
    std::vector<Token> tokens;
    std::istringstream stream(source);
    std::string word;

    while (stream >> word) {
        if (word == "func") {
            tokens.push_back(Token::FUNC);
        } else if (word == "return") {
            tokens.push_back(Token::RETURN);
        } else if (word == "(") {
            tokens.push_back(Token::LEFT_PAREN);
        } else if (word == ")") {
            tokens.push_back(Token::RIGHT_PAREN);
        } else if (word == ",") {
            tokens.push_back(Token::COMMA);
        } else if (isdigit(word[0])) {
            tokens.push_back(Token::NUMBER);
        } else {
            tokens.push_back(Token::IDENTIFIER);
        }
    }

    tokens.push_back(Token::END);
    return tokens;
}
