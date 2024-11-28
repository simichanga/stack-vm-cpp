#include "StackVM.cpp"
#include "Lexer.cpp"
#include "Parser.cpp"

int main() {
    // Example source code
    const std::string sourceCode = R"(
        # Insert slurs here
        PUSH 10
        PUSH 20
        ADD
        DEBUG
        PUSH 5
        MUL
        DEBUG
        HALT
    )";

    try {
        Lexer lexer(sourceCode);
        const auto tokens = lexer.tokenize();

        Parser parser(tokens);
        const auto instructions = parser.parse();

        StackVM vm;
        vm.run(instructions);
    } catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
    }

    return 0;
}
