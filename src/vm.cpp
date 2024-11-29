// vm.cpp
#include "vm.h"
#include <iostream>
#include <unordered_map>


void StackVM::loadProgram(const std::vector<std::pair<Opcode, std::string>>& p) {
    // DEBUG
    std::cout << "Program loaded!" << std::endl;
    program = p;
}

void StackVM::execute() {
    // DEBUG
    std::cout << "Executing program..." << std::endl;
    while (ip < program.size()) {
        executeOpcode(program[ip]);
        ip++;
    }
}

void StackVM::executeOpcode(const std::pair<Opcode, std::string>& opcode) {
    switch (opcode.first) {
        case Opcode::PUSH:
            stack.push_back(opcode.second);
        break;
        case Opcode::ADD: {
            int operand1 = std::stoi(stack.back()); stack.pop_back();
            int operand2 = std::stoi(stack.back()); stack.pop_back();
            stack.push_back(std::to_string(operand1 + operand2));
            break;
        }
        case Opcode::CALL: {
            std::cout << "Calling function: " << opcode.second << std::endl;
            // Jump to function code, execute its instructions
            break;
        }
        case Opcode::RET:
            std::cout << "Returning value" << std::endl;
        break;
        case Opcode::HALT:
            std::cout << "Halting execution" << std::endl;
        return;
    }
}
