1. Lexical Analysis (Tokenization)

    Purpose: Convert the raw source code into a series of tokens. Tokens are the smallest meaningful units of the language, such as keywords, identifiers, operators, literals, and punctuation.

    Input: Raw source code (e.g., func addOne(var num) { return num + 1; })

    Output: A stream of tokens.
        Example:

        [FUNC, IDENTIFIER(addOne), LPAREN, VAR, IDENTIFIER(num), RPAREN, LBRACE, RETURN, IDENTIFIER(num), PLUS, NUMBER(1), SEMICOLON, RBRACE]

    Process:
        Use a lexer (or tokenizer) to scan the source code.
        Match patterns (e.g., keywords, numbers, identifiers) using regular expressions.
        The lexer outputs tokens representing the smallest units of meaning.

2. Syntax Analysis (Parsing)

    Purpose: Analyze the token stream to understand the grammatical structure of the source code. This process builds an Abstract Syntax Tree (AST) that represents the syntactic structure of the code.

    Input: A stream of tokens.

    Output: An Abstract Syntax Tree (AST).
        Example AST:

        FunctionDeclaration
          ├── Name: addOne
          ├── Parameters
          │   └── Variable: num
          └── Body
              └── ReturnStatement
                  ├── Identifier: num
                  └── Addition
                      ├── Identifier: num
                      └── Literal: 1

    Process:
        Use a parser (often a recursive descent parser or using tools like LL or LR parsing).
        The parser verifies that the token stream adheres to the grammar of the language.
        It creates an AST, which represents the hierarchical structure of the program's components (functions, variables, expressions).

3. Semantic Analysis

    Purpose: Check the AST for semantic errors, ensuring the program is logically correct and consistent with the language's rules (e.g., type checking, scope resolution).

    Input: AST.

    Output: A semantically validated AST (possibly with additional information like types or symbol tables).

    Process:
        Type checking: Verify that operations and expressions use compatible types (e.g., int + float).
        Scope resolution: Ensure variables are declared before use and that they belong to the correct scope.
        Symbol table generation: A symbol table stores information about variables, functions, and their types.

4. Intermediate Representation (IR) Generation

    Purpose: Convert the semantically validated AST into an intermediate representation (IR), which is easier to manipulate and optimize than the original high-level source code.

    Input: Semantically validated AST.

    Output: Intermediate Representation (IR).

    Process:
        The IR can be in a variety of forms, such as:
            Three-Address Code (TAC): A low-level representation with operations like x = a + b.
            Control Flow Graph (CFG): A graph representing the flow of control in the program (used for optimization and analysis).
        The IR allows for easier optimization and can be translated to machine code or bytecode.

5. Optimization

    Purpose: Improve the IR by performing transformations that make the code more efficient, both in terms of speed and memory usage.

    Input: Intermediate Representation (IR).

    Output: Optimized IR.

    Process:
        Constant folding: Simplify constant expressions (e.g., replace 3 + 5 with 8).
        Dead code elimination: Remove code that doesn't affect the program's output (e.g., unused variables).
        Loop unrolling: Expand loops to reduce overhead (e.g., for i = 0 to 10 becomes multiple unrolled statements).
        Inlining: Replace function calls with the body of the function if possible.
        Register allocation: Optimize the use of CPU registers to minimize memory access.

6. Code Generation

    Purpose: Convert the optimized intermediate representation into the target code, which could be assembly language, machine code, or bytecode.

    Input: Optimized IR.

    Output: Target code (e.g., assembly or machine code).

    Process:
        Map operations in the IR to machine instructions (for a JIT compiler) or assembly instructions (for a traditional compiler).
        Handle calling conventions, stack management, and register allocation to ensure that the target code works correctly on the intended platform.
        For bytecode generation (e.g., for a virtual machine), the code is translated into platform-independent instructions.

7. Code Emission (Final Output)

    Purpose: Output the generated code, which can be executed on the target machine.

    Input: Assembly or machine code (or bytecode).

    Output: An executable program or bytecode.

    Process:
        If generating machine code, produce an executable file (e.g., .exe, .out).
        If generating bytecode (e.g., for a VM or JIT compiler), produce a bytecode file that can be executed by the virtual machine or runtime environment.
        Linking (if needed): If your program uses external libraries or modules, linking combines object files into a final executable.

8. Execution

    Purpose: The final step is running the generated code on a target system.

    Input: An executable or bytecode.

    Output: The execution result (e.g., output to the console or file).

    Process:
        If you're compiling to machine code, the program runs directly on the hardware.
        If you're compiling to bytecode, a virtual machine (VM) or runtime environment executes the bytecode.
