#include "botcraft/Utilities/StringUtilities.hpp"

namespace Botcraft
{
    const bool StartsWith(const std::string& mainStr, const std::string& toMatch)
    {
        return mainStr.find(toMatch) == 0;
    }

    const bool EndsWith(const std::string& mainStr, const std::string& toMatch)
    {
        if (toMatch.size() > mainStr.size())
        {
            return false;
        }
        return std::equal(toMatch.rbegin(), toMatch.rend(), mainStr.rbegin());
    }

    const std::vector<std::string> SplitString(const std::string& s, const char delimiter)
    {
        std::vector<std::string> tokens;
        std::string token;
        std::istringstream tokenStream(s);
        while (std::getline(tokenStream, token, delimiter))
        {
            tokens.push_back(token);
        }
        return tokens;
    }
} // Botcraft