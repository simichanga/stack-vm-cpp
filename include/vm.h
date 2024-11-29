// vm.h

#ifndef VM_H
#define VM_H

#include <vector>
#include <string>
#include <utility> // For std::pair
#include <unordered_map>

enum class Opcode {
    PUSH,
    ADD,
    CALL,
    RET,
    HALT,
};

class StackVM {
public:
    void loadProgram(const std::vector<std::pair<Opcode, std::string>>& program);
    void execute();

private:
    std::unordered_map<std::string, size_t> functionTable;
    std::vector<std::string> stack;
    std::vector<std::pair<Opcode, std::string>> program;
    size_t ip = 0;

    void executeOpcode(const std::pair<Opcode, std::string>& opcode);
};
#endif // VM_H
