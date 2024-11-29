#include "vm.h"
#include <vector>
#include <string>
#include <iostream>

int main() {
    StackVM vm;

    // Modify the program to use Opcode and std::string
    std::vector<std::pair<Opcode, std::string>> program = {
        {Opcode::PUSH, "1"},  // Push 1 onto the stack
        {Opcode::PUSH, "2"},  // Push 2 onto the stack
        {Opcode::ADD, ""}     // Add the top two elements of the stack
    };

    vm.loadProgram(program);  // This will call loadProgram
    vm.execute();              // This will call execute

    return 0;
}
