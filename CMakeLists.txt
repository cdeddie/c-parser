cmake_minimum_required(VERSION 3.12)
project(c-parser)

set(CMAKE_CXX_STANDARD 17)

# Add main source files and stores in MAIN_SRC_LIST. Note: Globbing is not recommended unless CONFIGURE_DEPENDS is used
file(GLOB_RECURSE MAIN_SRC_LIST CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/src/*.cpp")

# Filters the list 'MAIN_SRC_LIST'. This list will be used to create executables for the test suites
list(FILTER MAIN_SRC_LIST EXCLUDE REGEX "${PROJECT_SOURCE_DIR}/src/main.cpp$")

# Create exe for main
add_executable(main ${MAIN_SRC_LIST} "${PROJECT_SOURCE_DIR}/src/main.cpp")

# Include hpp files for main.exe
target_include_directories(main PRIVATE "${PROJECT_SOURCE_DIR}/include")

# Declare test suites
set(TEST_SUITES LexerTestSuite ParserTestSuite PointerTestSuite)

foreach(TEST_SUITE ${TEST_SUITES})
    # Test source files.
    file(GLOB_RECURSE TEST_SRC_LIST CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/tests/${TEST_SUITE}.cpp")

    # Test suite exe
    add_executable(${TEST_SUITE} ${MAIN_SRC_LIST} ${TEST_SRC_LIST})

    # Include hpp files for each test suite
    target_include_directories(${TEST_SUITE} PRIVATE "${PROJECT_SOURCE_DIR}/include")

    # Rename main function to TestSuiteMain
    set_target_properties(${TEST_SUITE} PROPERTIES COMPILE_DEFINITIONS "TestSuiteMain=main")
endforeach()