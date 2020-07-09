#pragma once

#include <vector>
#include <string>
#include <sstream>

namespace Botcraft
{
    const bool StartsWith(const std::string& mainStr, const std::string& toMatch);

    const bool EndsWith(const std::string& mainStr, const std::string& toMatch);

    const std::vector<std::string> SplitString(const std::string& s, const char delimiter);
}