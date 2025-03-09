# C Parser Project

## Intro
This project is a C parser written in C++. It takes C code as input and generates an Abstract Syntax Tree (AST). The AST can be output as a plain text tree representation, or as JSON.

Compiled for the web using

```powershell
em++ -std=c++17 -lembind -sMODULARIZE=1 -sEXPORT_ES6=1 -sNO_DISABLE_EXCEPTION_CATCHING -o main.js $(Get-ChildItem -Recurse -Filter "*.cpp" -Path src | Select-Object -ExpandProperty FullName) -Iinclude
```

## WARNING
This project is not a complete C parser. There are major language features that are missing. This is simply a personal side project. Here is a list of known bugs/missing features:

- Structs
- Comments
- true/false values - use 1, 0
- Array as a parameter (e.g. ```int func(int arr[]); ```) - use pointers instead
- Compound assignment operators (e.g. ```+=```, ```-=```)
- Declaring global variables after the last function in a file.
- Defining/declaring multiple variables in one line.
- And likely many more missing features/bugs, C is quite broad!