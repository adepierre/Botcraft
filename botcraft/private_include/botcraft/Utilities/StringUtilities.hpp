#pragma once

#include <vector>
#include <string>

namespace Botcraft::Utilities
{
    bool StartsWith(const std::string& mainStr, const std::string& toMatch);

    bool EndsWith(const std::string& mainStr, const std::string& toMatch);

    std::vector<std::string> SplitString(const std::string& s, const char delimiter);

#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
    std::vector<unsigned char> DecodeBase64(const std::string& s);

    std::vector<unsigned char> RSAToBytes(const std::string& s);

    long long int TimestampMilliFromISO8601(const std::string& s);
#endif
}
