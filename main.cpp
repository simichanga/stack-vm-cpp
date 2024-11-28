#include <iostream>
#include <vector>
#include <stack>
#include <stdexcept>
#include <functional>
#include <thread>
#include <future>

class StackVM {
public:
    // Run the program
    void run(const std::vector<std::function<void()>>& program) {
        programCounter = 0;
        while (programCounter < program.size()) {
            program[programCounter]();
            ++programCounter;
        }
    }

    // Push a value onto the stack
    void push(int value) {
        stack.push(value);
    }

    // Pop a value from the stack
    int pop() {
        if (stack.empty()) {
            throw std::runtime_error("Stack underflow");
        }
        int value = stack.top();
        stack.pop();
        return value;
    }

    // Generic binary operation handler
    void binaryOperation(const std::string& opName, const std::function<int(int, int)>& operation) {
        if (stack.size() < 2) {
            throw std::runtime_error("Insufficient operands for " + opName);
        }
        int b = pop();
        int a = pop();
        push(operation(a, b));
    }

    // Arithmetic operations
    void add() { binaryOperation("ADD", [](int a, int b) { return a + b; }); }
    void sub() { binaryOperation("SUB", [](int a, int b) { return a - b; }); }
    void mul() { binaryOperation("MUL", [](int a, int b) { return a * b; }); }
    void div() {
        binaryOperation("DIV", [](int a, int b) {
            if (b == 0) throw std::runtime_error("Division by zero");
            return a / b;
        });
    }

    // Bitwise operations
    void bitwiseAnd() { binaryOperation("AND", [](int a, int b) { return a & b; }); }
    void bitwiseOr() { binaryOperation("OR", [](int a, int b) { return a | b; }); }
    void bitwiseXor() { binaryOperation("XOR", [](int a, int b) { return a ^ b; }); }
    void bitwiseNot() {
        if (stack.empty()) throw std::runtime_error("Stack underflow in NOT");
        int value = pop();
        push(~value);
    }

    // Comparison operators
    void equal() { binaryOperation("EQUAL", [](int a, int b) { return a == b ? 1 : 0; }); }
    void lessThan() { binaryOperation("LESS_THAN", [](int a, int b) { return a < b ? 1 : 0; }); }
    void greaterThan() { binaryOperation("GREATER_THAN", [](int a, int b) { return a > b ? 1 : 0; }); }

    // Debugging utilities
    void debugStack() const {
        std::stack<int> temp = stack;
        std::cout << "Stack: ";
        while (!temp.empty()) {
            std::cout << temp.top() << " ";
            temp.pop();
        }
        std::cout << '\n';
    }

    // Support for Memory Access
    void load(int address) {
        if (address < 0 || address >= memory.size()) {
            throw std::runtime_error("Memory access out of bounds in LOAD");
        }
        push(memory[address]);
    }

    void store(int address) {
        if (address < 0 || address >= memory.size()) {
            throw std::runtime_error("Memory access out of bounds in STORE");
        }
        if (stack.empty()) {
            throw std::runtime_error("Stack underflow in STORE");
        }
        memory[address] = pop();
    }

    // Support for function calls and recursion
    void call(size_t target) {
        callStack.push(programCounter); // Save current PC
        programCounter = target - 1;   // Jump to target
    }

    void ret() {
        if (callStack.empty()) {
            throw std::runtime_error("Call stack underflow in RET");
        }
        programCounter = callStack.top();
        callStack.pop();
    }

    // I/O operations
    /*
    vm.input();  // User enters a value
    vm.push(2);  // Push 2
    vm.mul();    // Multiply input by 2
    vm.output(); // Print result
     */
    void input() {
        int value;
        std::cout << "Enter a number: ";
        std::cin >> value;
        push(value);
    }

    void output() {
        if (stack.empty()) throw std::runtime_error("Stack underflow in OUTPUT");
        int value = pop();
        std::cout << "Output: " << value << '\n';
    }

    // Labels and dynamic jumping
    void defineLabel(const std::string& label, size_t address) {
        labels[label] = address;
    }

    void jumpToLabel(const std::string& label) {
        if (!labels.contains(label)) {
            throw std::runtime_error("Undefined label: " + label);
        }
        // TODO: implement jump method
        // jump(labels[label]);
    }

    // Basic multithreading by spawning independent instruction streams
    /*
    std::vector<std::function<void()>> subProgram = {
        [&] { vm.push(10); },
        [&] { vm.push(20); },
        [&] { vm.add(); },
        [&] { vm.debugStack(); }
    };
    vm.runAsync(subProgram);
     */
    void runAsync(const std::vector<std::function<void()>>& program) {
        std::thread([this, program]() {
            try {
                run(program);
            } catch (const std::exception& e) {
                std::cerr << "Thread error: " << e.what() << '\n';
            }
        }).detach();
    }

private:
    std::stack<int> stack;
    size_t programCounter = 0;
    std::vector<int> memory = std::vector<int>(256, 0); // Memory space of 256 integers
    std::stack<size_t> callStack;
    std::unordered_map<std::string, size_t> labels;
};

int main() {
    StackVM vm;

    // TEST: arithmetic ops
    std::vector<std::function<void()>> program = {
        [&] { vm.push(10); },
        [&] { vm.push(20); },
        [&] { vm.add(); },
        [&] { vm.debugStack(); },
        [&] { vm.push(5); },
        [&] { vm.mul(); },
        [&] { vm.debugStack(); },
    };

    // TEST: memory
    // std::vector<std::function<void()>> program {
    //     [&] { vm.push(42); },       // Push 42 onto the stack
    //     [&] { vm.store(10); },      // Store it at memory address 10
    //     [&] { vm.load(10); },       // Load the value from memory address 10 back to the stack
    //     [&] { vm.debugStack(); },
    // };

    // TEST: bitwise ops
    // std::vector<std::function<void()>> program {
    //     [&] { vm.push(5); },        // Push 5 (binary 0101)
    //     [&] { vm.push(3); },        // Push 3 (binary 0011)
    //     [&] { vm.bitwiseAnd(); },       // Result: 1 (binary 0001)
    //     [&] { vm.debugStack(); },
    // };

    // TEST: comparison ops
    // std::vector<std::function<void()>> program {
    //     [&] { vm.push(10); },
    //     [&] { vm.push(20); },
    //     [&] { vm.lessThan(); },     // Stack will now have 1 (true)
    //     [&] { vm.debugStack(); },
    // };

    // TEST: function calls
    // std::vector<std::function<void()>> program = {
    //     [&] { vm.push(5); },          // Push 5
    //     [&] { vm.call(3); },          // Call function at address 3
    //     [&] { vm.halt(); },           // TODO: End program
    //     [&] { vm.push(10); },         // Function start: Push 10
    //     [&] { vm.add(); },            // Add
    //     [&] { vm.ret(); }             // Return
    // };

    // TEST: I/O ops

    // TEST: Labels & Dynamic Jumping

    // TEST: Multithreading
    // std::vector<std::function<void()>> subProgram = {
    //     [&] { vm.push(10); },
    //     [&] { vm.push(20); },
    //     [&] { vm.add(); },
    //     [&] { vm.output(); }
    // };

    // Run the program
    try {
        vm.run(program);
    } catch (const std::exception& e) {
        std::cerr << "Runtime error: " << e.what() << '\n';
    }

    return 0;
}
