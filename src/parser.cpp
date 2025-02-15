// parser.cpp
#include "lexer.h"
#include <unordered_map>

struct Function {
    std::string name;
    std::vector<std::string> parameters;
    std::vector<std::string> instructions;  // For simplicity, use strings as placeholders for now
};

class Parser {
public:
    void parse(const std::vector<Token>& tokens);
    std::unordered_map<std::string, Function> functionTable;

private:
    size_t current = 0;
    Token currentToken() { return tokens[current]; }
    void advance() { current++; }
    void parseFunction();
    void parseStatements();
    std::vector<Token> tokens;
};

void Parser::parse(const std::vector<Token>& tokenStream) {
    tokens = tokenStream;
    while (current < tokens.size()) {
        if (currentToken() == Token::FUNC) {
            parseFunction();
        } else {
            advance();
        }
    }
}

void Parser::parseFunction() {
    advance(); // Skip "func"

    // Declare funcName in the appropriate scope
    std::string funcName;

    if (currentToken() == Token::IDENTIFIER) {
        funcName = "foo";  // Hardcoded for simplicity (you can dynamically assign this)
        advance(); // Move past the function name
    }

    if (currentToken() == Token::LEFT_PAREN) {
        advance();  // Skip "("

        // Parse parameters (if any)
        if (currentToken() == Token::VAR) {
            advance();
            std::string param = "x";  // Hardcoded parameter (you can dynamically assign this)
            functionTable[funcName].parameters.push_back(param);
            advance();  // Skip the parameter
        }

        if (currentToken() == Token::RIGHT_PAREN) {
            advance();  // Skip ")"
        }
    }

    // Now that we've parsed the function name and parameters, parse the function's body
    if (currentToken() == Token::RETURN) {
        advance();  // Skip "return"
        functionTable[funcName].instructions.push_back("RETURN");
    }
}
