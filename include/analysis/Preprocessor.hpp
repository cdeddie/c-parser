#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include <sstream>

class Preprocessor 
{
public:
    Preprocessor(std::string code);
    void process();
    std::unordered_map<std::string, std::string> getMacros() const;
    std::vector<std::string> getPaths() const;

private:
    std::string code;
    std::unordered_map<std::string, std::string> macros;    // 
    std::vector<std::string> paths;
    void handleDirective(const std::string& line);
};