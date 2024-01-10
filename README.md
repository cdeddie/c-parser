# C Parser Project

## Intro
This project is a C parser written in C++. It takes C code as input and generates an Abstract Syntax Tree (AST). The AST can be output in either JSON format or as a plain text tree representation.

## Requirements
- C++ compiler with support for at least C++17 (e.g., GCC 8 or later, Clang 5 or later)
- CMake V3.1 (for building the project)

## Building the Project
To build the project, follow these steps:

1. Clone the repository or download the source code.
2. Navigate to the root directory of the project.
3. Create a build directory and navigate into it:
   ```bash
   mkdir build && cd build
   cmake ..
   make main

Note: Make sure CMake and your C++ compiler are properly set up and in your PATH.

## Usage
After building the project, you can run the parser with the following commands.

### Running the Parser
To run the parser, use the executable generated in the build directory. There are two main ways to provide input to the parser:

#### Inline input
To run the parser with inline input, use:
   ```bash
   echo "your C code here" | ./main [output_format]
   ```

Replace [output_format] with 1 for JSON output or 2 for plain text output.

#### File Input
To use a .c file as input, first create or place your .c file in the build directory. Then run:
   ```bash
   ./main [output_format] < file.c
   ```

Replace file.c with the name of the C file, and [output_format] as above.

## WARNING
This project is not a complete C parser. There are major language features that are missing. This is simply a personal side project. Here is a list of known bugs/missing features:

- Preprocessor directives - ```#include```, ```#define``` etc.
- Structs
- Comments
- Array parameters (e.g. ```int func(int arr[]); ```) - use pointers instead
- Compound assignment operators (e.g. ```+=```, ```-=```)
- Declaring global variables after the last function in a file.
- Defining/declaring multiple variables in one line.
- And likely many more missing features/bugs, C is quite broad!
