#include "analysis/Preprocessor.hpp"

Preprocessor::Preprocessor(std::string code) : code(code)
{

}

void Preprocessor::process()
{
    std::istringstream stream(code);
    std::string line;
    while (std::getline(stream, line))
        handleDirective(line);
}

std::unordered_map<std::string, std::string> Preprocessor::getMacros() const
{
    return macros;
}

std::vector<std::string> Preprocessor::getPaths() const
{
    return paths;
}

std::string normaliseSpaces(const std::string& line)
{
    std::string normalised;
    bool inSpace = false;
    for (char c : line)
    {
        if (std::isspace(c))
        {
            if (!inSpace)
            {
                normalised += ' ';
                inSpace = true;
            }
        }
        else
        {
            normalised += c;
            inSpace = false;
        }
    }
    return normalised;
}

void Preprocessor::handleDirective(const std::string& line)
{
    std::string normalisedLine = normaliseSpaces(line);

    if (normalisedLine.find("#define") == 0) {
        size_t nameStartPos = 8;
        size_t spacePos = normalisedLine.find(' ', nameStartPos);
        if (spacePos != std::string::npos) {
            std::string name = normalisedLine.substr(nameStartPos, spacePos - nameStartPos);
            std::string value = normalisedLine.substr(spacePos + 1);
            macros[name] = value;
        }
    }
    
    else if (normalisedLine.find("#include") == 0) {
        std::string path = normalisedLine.substr(9);
        paths.push_back(path);
    }
}