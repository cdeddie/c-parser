cmake_minimum_required(VERSION 3.1)
project(compiler)

set(CMAKE_CXX_STANDARD 17)

# Add main source files
file(GLOB_RECURSE MAIN_SRC_LIST CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/src/*.cpp")

# Exclude main.cpp from being included in the tests
list(FILTER MAIN_SRC_LIST EXCLUDE REGEX "${PROJECT_SOURCE_DIR}/src/main.cpp$")

# Add test source files
file(GLOB_RECURSE TESTS_SRC_LIST CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/tests/*.cpp")

# Create executable for the main code
add_executable(main ${MAIN_SRC_LIST} "${PROJECT_SOURCE_DIR}/src/main.cpp")

# Create executable for the tests
add_executable(LexerTest ${MAIN_SRC_LIST} ${TESTS_SRC_LIST})

# Use target_include_directories to include directories for specific targets
target_include_directories(main PRIVATE ${FINAL_INCLUDE_DIRS})
target_include_directories(LexerTest PRIVATE ${FINAL_INCLUDE_DIRS})

target_include_directories(main PRIVATE 
    "${PROJECT_SOURCE_DIR}/include"
    "${PROJECT_SOURCE_DIR}/include/lexer"
    "${PROJECT_SOURCE_DIR}/include/parser"
    "${PROJECT_SOURCE_DIR}/include/parser/AST")

target_include_directories(LexerTest PRIVATE 
    "${PROJECT_SOURCE_DIR}/include"
    "${PROJECT_SOURCE_DIR}/include/lexer"
    "${PROJECT_SOURCE_DIR}/include/parser"
    "${PROJECT_SOURCE_DIR}/include/parser/AST")