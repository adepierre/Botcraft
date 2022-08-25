#include "botcraft/Utilities/StringUtilities.hpp"
#include "botcraft/Utilities/Logger.hpp"


#if PROTOCOL_VERSION > 758
#include <array>
#include <ctime>
#include <iomanip>
#endif

namespace Botcraft
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

#if PROTOCOL_VERSION > 758
    std::vector<unsigned char> DecodeBase64(const std::string& s)
    {
        static std::array<unsigned char, 128> constexpr decode_table {
            64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
            64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
            64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 62, 64, 64, 64, 63,
            52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 64, 64, 64, 64, 64, 64,
            64,  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14,
            15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 64, 64, 64, 64, 64,
            64, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40,
            41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 64, 64, 64, 64, 64
        };

        if (s.size () == 0)
        {
            return {};
        }

        if (s.size() % 4 != 0)
        {
            LOG_ERROR("Base64 string size not a multiple of 4");
            return {};
        }

        int output_size = s.size() / 4 * 3;

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

    int IsLeap(const int year)
    {
        if (year % 400 == 0)
        {
            return 1;
        }
        if (year % 100 == 0)
        {
            return 0;
        }
        if (year % 4 == 0)
        {
            return 1;
        }
        return 0;
    }

    int DaysFrom0(const int year)
    {
        return 365 * (year - 1) + ((year - 1) / 400) - ((year - 1) / 100) + ((year - 1) / 4);
    }

    int DaysFrom1970(int32_t year)
    {
        return DaysFrom0(year) - DaysFrom0(1970);
    }

    int DaysFrom1Jan(const int year, const int month, const int day)
    {
        static constexpr std::array<std::array<int, 12>, 2> days =
        { {
          { 0,31,59,90,120,151,181,212,243,273,304,334},
          { 0,31,60,91,121,152,182,213,244,274,305,335}
        } };

        return days[IsLeap(year)][month - 1] + day - 1;
    }

    long long int TimestampMilliFromISO8601(const std::string& s)
    {
        std::tm t{};
        std::stringstream iso8601(s);
        iso8601 >> std::get_time(&t, "%Y-%m-%dT%H:%M:%S");

        if (iso8601.fail())
        {
            LOG_ERROR("Error trying to parse ISO 8601 string: " << s);
            return 0;
        }

        std::vector<std::string> splitted_expires = SplitString(s, '.');
        if (EndsWith(splitted_expires.back(), "Z"))
        {
            splitted_expires.back() = splitted_expires.back().substr(0, splitted_expires.back().size() - 1);
        }
        const long long int ms = std::stol(splitted_expires.back()) / 1000;

        const int year = t.tm_year + 1900;
        const int month = t.tm_mon + 1;
        const int day = t.tm_mday;
        const int day_of_year = DaysFrom1Jan(year, month, day);
        const int days_since_epoch = DaysFrom1970(year) + day_of_year;

        const long long int sec = 3600 * 24 * days_since_epoch + 3600 * t.tm_hour + 60 * t.tm_min + t.tm_sec;

        return sec * 1000 + ms;
    }
#endif
} // Botcraft
