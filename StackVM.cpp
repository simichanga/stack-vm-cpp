#pragma once

#include <iostream>
#include <vector>
#include <stack>
#include <stdexcept>
#include <functional>


class StackVM {
public:
    enum class Opcode {
        PUSH,
        POP,
        ADD,
        SUB,
        MUL,
        DIV,
        LOAD,
        STORE,
        JUMP,
        JUMP_IF,
        CALL,
        RET,
        HALT,
        DEBUG
    };

    struct Instruction {
        Opcode opcode;
        int operand = 0; // Optional operand
    };


    explicit StackVM(size_t memorySize = 256) : memory(memorySize, 0) {}

    // Execute the program
    void run(const std::vector<Instruction>& program) {
        programCounter = 0;
        callStack = {};
        running = true;

        while (running && programCounter < program.size()) {
            const auto& instr = program[programCounter];
            execute(instr);
            programCounter++;
        }
    }

    // Debugging utility
    void debugState() const {
        std::cout << "Program Counter: " << programCounter << "\n";
        std::cout << "Stack: ";
        for (auto s : stackDump()) {
            std::cout << s << " ";
        }
        std::cout << "\n";
    }

private:
    std::stack<int> stack;
    std::vector<int> memory;
    std::stack<size_t> callStack;
    size_t programCounter = 0;
    bool running = true;

    void execute(const Instruction& instr) {
        switch (instr.opcode) {
            case Opcode::PUSH:
                push(instr.operand);
                break;
            case Opcode::POP:
                pop();
                break;
            case Opcode::ADD:
                binaryOperation("ADD", [](int a, int b) { return a + b; });
                break;
            case Opcode::SUB:
                binaryOperation("SUB", [](int a, int b) { return a - b; });
                break;
            case Opcode::MUL:
                binaryOperation("MUL", [](int a, int b) { return a * b; });
                break;
            case Opcode::DIV:
                binaryOperation("DIV", [](int a, int b) {
                    if (b == 0) throw std::runtime_error("Division by zero");
                    return a / b;
                });
                break;
            case Opcode::LOAD:
                push(memory[instr.operand]);
                break;
            case Opcode::STORE:
                memory[instr.operand] = pop();
                break;
            case Opcode::JUMP:
                programCounter = instr.operand - 1;
                break;
            case Opcode::JUMP_IF:
                if (pop() != 0) programCounter = instr.operand - 1;
                break;
            case Opcode::CALL:
                callStack.push(programCounter);
                programCounter = instr.operand - 1;
                break;
            case Opcode::RET:
                if (callStack.empty()) throw std::runtime_error("Call stack underflow in RET");
                programCounter = callStack.top();
                callStack.pop();
                break;
            case Opcode::HALT:
                running = false;
                break;
            case Opcode::DEBUG:
                debugState();
                break;
            default:
                throw std::runtime_error("Unknown opcode");
        }
    }

    void push(int value) { stack.push(value); }
    int pop() {
        if (stack.empty()) throw std::runtime_error("Stack underflow");
        int value = stack.top();
        stack.pop();
        return value;
    }

    void binaryOperation(const std::string& opName, const std::function<int(int, int)>& operation) {
        if (stack.size() < 2) throw std::runtime_error("Insufficient operands for " + opName);
        int b = pop();
        int a = pop();
        push(operation(a, b));
    }

    [[nodiscard]]
    std::vector<int> stackDump() const {
        std::vector<int> dump;
        std::stack<int> temp = stack;
        while (!temp.empty()) {
            dump.push_back(temp.top());
            temp.pop();
        }
        return dump;
    }
};

const std::unordered_map<std::string, StackVM::Opcode> opcodeMap = {
    {"PUSH", StackVM::Opcode::PUSH}, {"POP", StackVM::Opcode::POP},
    {"ADD", StackVM::Opcode::ADD}, {"SUB", StackVM::Opcode::SUB},
    {"MUL", StackVM::Opcode::MUL}, {"DIV", StackVM::Opcode::DIV},
    {"LOAD", StackVM::Opcode::LOAD}, {"STORE", StackVM::Opcode::STORE},
    {"JUMP", StackVM::Opcode::JUMP}, {"JUMP_IF", StackVM::Opcode::JUMP_IF},
    {"CALL", StackVM::Opcode::CALL}, {"RET", StackVM::Opcode::RET},
    {"HALT", StackVM::Opcode::HALT}, {"DEBUG", StackVM::Opcode::DEBUG}
};
