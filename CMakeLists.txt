cmake_minimum_required(VERSION 3.1)
project(compiler)

set(CMAKE_CXX_STANDARD 17)

# Add main source files
file(GLOB_RECURSE MAIN_SRC_LIST CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/src/*.cpp")

# Exclude main.cpp from being included in the tests
list(FILTER MAIN_SRC_LIST EXCLUDE REGEX "${PROJECT_SOURCE_DIR}/src/main.cpp$")

# Add test source files. This configures the variable TESTS_SRC_LIST
file(GLOB_RECURSE TESTS_SRC_LIST CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/tests/*.cpp")

# Create executable for the main code
add_executable(main ${MAIN_SRC_LIST} "${PROJECT_SOURCE_DIR}/src/main.cpp")

# Create executable for the ASTTest
add_executable(ASTTest ${MAIN_SRC_LIST} "${PROJECT_SOURCE_DIR}/tests/ASTTest.cpp")

# Create executable for LexerTest
add_executable(LexerTest ${MAIN_SRC_LIST} "${PROJECT_SOURCE_DIR}/tests/LexerTest.cpp")

# Include directories for specific targets
target_include_directories(main PRIVATE "${PROJECT_SOURCE_DIR}/include")
target_include_directories(LexerTest PRIVATE "${PROJECT_SOURCE_DIR}/include")
target_include_directories(ASTTest PRIVATE "${PROJECT_SOURCE_DIR}/include")

# Rename main function to LexerTestMain and ASTTestMain
set_target_properties(LexerTest PROPERTIES COMPILE_DEFINITIONS "LexerTestMain=main")
set_target_properties(ASTTest PROPERTIES COMPILE_DEFINITIONS "ASTTestMain=main")

