#include "vm.h"
#include <vector>
#include <string>
#include <iostream>

int main() {
    StackVM vm;

    // Modify the program to use Opcode and std::string
    std::vector<std::pair<Opcode, std::string>> program = {
        {Opcode::PUSH, "1"},
        {Opcode::ADD, "0"}
    };

    vm.loadProgram(program);  // This will call loadProgram
    vm.execute();              // This will call execute

    return 0;
}
