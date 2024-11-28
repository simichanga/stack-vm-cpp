#pragma once
#include "StackVM.cpp"
#include <sstream>

// Token types
enum class TokenType {
    OPCODE,
    OPERAND,
    END_OF_LINE
};

// Token structure
struct Token {
    TokenType type;
    std::string value;
};

// Lexer to tokenize source code
class Lexer {
public:
    explicit Lexer(const std::string& source) : source(source) {}

    std::vector<Token> tokenize() {
        std::vector<Token> tokens;
        std::istringstream stream(source);
        std::string line;

        while (std::getline(stream, line)) {
            tokenizeLine(line, tokens);
        }

        return tokens;
    }

private:
    std::string source;

    void tokenizeLine(const std::string& line, std::vector<Token>& tokens) {
        std::istringstream lineStream(line);
        std::string word;

        while (lineStream >> word) {
            // Skip comments and blank lines
            if (word[0] == '#') return;

            if (isOpcode(word)) {
                tokens.push_back({TokenType::OPCODE, word});
            } else if (isNumber(word)) {
                tokens.push_back({TokenType::OPERAND, word});
            } else {
                throw std::runtime_error("Invalid token: " + word);
            }
        }
        tokens.push_back({TokenType::END_OF_LINE, ""});
    }

    bool isOpcode(const std::string& word) {
        return opcodeMap.find(word) != opcodeMap.end();
    }

    bool isNumber(const std::string& word) {
        return !word.empty() && std::all_of(word.begin(), word.end(), ::isdigit);
    }
};
