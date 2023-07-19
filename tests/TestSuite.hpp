#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <functional>

class TestSuite
{
public:
    virtual ~TestSuite() = default;

    void run()
    {
        runTests();
        std::cout << "\033[32m" << "All tests passed" << "\033[0m" << std::endl;
    }

protected:
    virtual void runTests() = 0;

    void runTest(const std::string& description, const std::function<void()>& test)
    {
        std::cout << "\033[1m" << "----- Testing: " << description << " -----" << "\033[0m" << std::endl;
        try
        {
            test();
            std::cout << "\033[32m" << "Test passed: " << description << "\n" << "\033[0m";
        }
        catch(const std::exception& e)
        {
            std::cerr << "\033[31m" << description << " failed: " << e.what() << '\n' << "\033[0m";
        }
    }

    std::stringstream loadTestFile(const std::string& relativePath)
    {
        std::string currentFile(__FILE__);
        std::string basePath = currentFile.substr(0, currentFile.find_last_of("/\\"));
        std::string filePath = basePath + relativePath;

        std::ifstream inputFile(filePath);
        if (!inputFile.is_open())
        {
            throw std::runtime_error("Failed to open file: " + filePath);
        }

        std::stringstream fileStream;
        fileStream << inputFile.rdbuf();
        inputFile.close();

        return fileStream;
    }
};