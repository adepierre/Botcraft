#include "botcraft/Utilities/StringUtilities.hpp"
#include "botcraft/Utilities/Logger.hpp"


#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
#include <array>
#include <ctime>
#include <iomanip>
#endif

namespace Botcraft::Utilities
{
    bool StartsWith(const std::string& mainStr, const std::string& toMatch)
    {
        return mainStr.find(toMatch) == 0;
    }

    bool EndsWith(const std::string& mainStr, const std::string& toMatch)
    {
        if (toMatch.size() > mainStr.size())
        {
            return false;
        }
        return std::equal(toMatch.rbegin(), toMatch.rend(), mainStr.rbegin());
    }

    bool Contains(const std::string& mainStr, const std::string& toFind)
    {
        return mainStr.find(toFind) != std::string::npos;
    }

    std::vector<std::string> SplitString(const std::string& s, const char delimiter)
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

    std::vector<std::string> SplitString(const std::string& s, const std::string& delimiter)
    {
        const size_t delimiter_size = delimiter.size();
        size_t start = 0;
        size_t end = 0;
        std::vector<std::string> tokens;

        while ((end = s.find(delimiter, start)) != std::string::npos)
        {
            tokens.push_back(s.substr(start, end - start));
            start = end + delimiter_size;
        }

        tokens.push_back(s.substr(start));

        return tokens;
    }

#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
    std::vector<unsigned char> DecodeBase64(const std::string& s)
    {
        static std::array<unsigned char, 128> constexpr decode_table{
            64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
            64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
            64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 62, 64, 64, 64, 63,
            52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 64, 64, 64, 64, 64, 64,
            64,  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14,
            15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 64, 64, 64, 64, 64,
            64, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40,
            41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 64, 64, 64, 64, 64
        };

        if (s.size() == 0)
        {
            return {};
        }

        if (s.size() % 4 != 0)
        {
            LOG_ERROR("Base64 string size not a multiple of 4");
            return {};
        }

        const size_t output_size = s.size() / 4 * 3;

        std::vector<unsigned char> output;
        output.reserve(output_size);

        for (int i = 0; i < s.size(); i += 4)
        {
            const unsigned char c1 = s[i + 0] == '=' ? 0 : decode_table[static_cast<unsigned char>(s[i + 0])];
            const unsigned char c2 = s[i + 1] == '=' ? 0 : decode_table[static_cast<unsigned char>(s[i + 1])];
            const unsigned char c3 = s[i + 2] == '=' ? 0 : decode_table[static_cast<unsigned char>(s[i + 2])];
            const unsigned char c4 = s[i + 3] == '=' ? 0 : decode_table[static_cast<unsigned char>(s[i + 3])];

            const unsigned int bytes = (c1 << 18) | (c2 << 12) | (c3 << 6) | (c4 << 0);

            output.push_back((bytes >> 16) & 0xFF);
            output.push_back((bytes >> 8) & 0xFF);
            output.push_back((bytes >> 0) & 0xFF);
        }

        // If last character is a padding, we'll have one less byte
        if (s.back() == '=')
        {
            output.pop_back();
        }
        // If second last character is a padding, we'll have two less bytes
        if (s[s.size() - 2] == '=')
        {
            output.pop_back();
        }

        return output;
    }

    std::vector<unsigned char> RSAToBytes(const std::string& s)
    {
        const std::vector<std::string> splitted = SplitString(s, '\n');
        std::string base64 = "";
        for (int i = 1; i < splitted.size() - 1; ++i)
        {
            base64 += splitted[i];
        }
        return DecodeBase64(base64);
    }
#endif
} // Botcraft::Utilities
