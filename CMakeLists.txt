cmake_minimum_required(VERSION 3.1)
project(c-parser)

set(CMAKE_CXX_STANDARD 17)

# Add main source files
file(GLOB_RECURSE MAIN_SRC_LIST CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/src/*.cpp")

# Exclude main.cpp from being included in the tests
list(FILTER MAIN_SRC_LIST EXCLUDE REGEX "${PROJECT_SOURCE_DIR}/src/main.cpp$")

# Create executable for the main code
add_executable(main ${MAIN_SRC_LIST} "${PROJECT_SOURCE_DIR}/src/main.cpp")

# Include directories for main target
target_include_directories(main PRIVATE "${PROJECT_SOURCE_DIR}/include")

# Test Suites
set(TEST_SUITES LexerTestSuite ParserTestSuite)

foreach(TEST_SUITE ${TEST_SUITES})
    # Add test source files.
    file(GLOB_RECURSE TEST_SRC_LIST CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/tests/${TEST_SUITE}.cpp")

    # Create executable for the TestSuite
    add_executable(${TEST_SUITE} ${MAIN_SRC_LIST} ${TEST_SRC_LIST})

    # Include directories for specific targets
    target_include_directories(${TEST_SUITE} PRIVATE "${PROJECT_SOURCE_DIR}/include")

    # Rename main function to TestSuiteMain
    set_target_properties(${TEST_SUITE} PROPERTIES COMPILE_DEFINITIONS "TestSuiteMain=main")
endforeach()