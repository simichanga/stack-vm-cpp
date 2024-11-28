class Parser {
public:
    explicit Parser(const std::vector<Token>& tokens) : tokens(tokens), index(0) {}

    std::vector<StackVM::Instruction> parse() {
        std::vector<StackVM::Instruction> instructions;

        while (index < tokens.size()) {
            if (tokens[index].type == TokenType::END_OF_LINE) {
                index++; // Skip end-of-line tokens
                continue;
            }
            instructions.push_back(parseInstruction());
        }

        return instructions;
    }

private:
    const std::vector<Token>& tokens;
    size_t index;

    StackVM::Instruction parseInstruction() {
        if (tokens[index].type != TokenType::OPCODE) {
            throw std::runtime_error("Expected an opcode at token index " + std::to_string(index));
        }

        std::string opcode = tokens[index++].value;
        int operand = 0;

        if (needsOperand(opcode)) {
            if (index >= tokens.size() || tokens[index].type != TokenType::OPERAND) {
                throw std::runtime_error("Expected an operand for opcode " + opcode);
            }
            operand = std::stoi(tokens[index++].value);
        }

        return {toOpcode(opcode), operand};
    }

    bool needsOperand(const std::string& opcode) {
        return opcode == "PUSH" || opcode == "LOAD" || opcode == "STORE" || opcode == "JUMP" || opcode == "JUMP_IF" || opcode == "CALL";
    }

    StackVM::Opcode toOpcode(const std::string& opcode) {
        return opcodeMap.at(opcode);
    }
};
