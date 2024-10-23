#pragma once

#include <array>
#include <stdexcept>
#include <string_view>

namespace ProtocolCraft
{
    namespace Internal
    {
        /// @brief Get the size of a string_view once converted to snake_case
        /// @param str string to convert to snake_case
        /// @return Number of characters in the snake_case string
        constexpr size_t GetSnakeCaseSize(std::string_view str)
        {
            size_t size = 0;
            for (size_t i = 0; i < str.length(); ++i)
            {
                if (i > 0 &&
                    ((str[i] >= 'A' && str[i] <= 'Z') ||
                        (str[i] >= '0' && str[i] <= '9' && (str[i - 1] < '0' || str[i - 1] > '9')))
                )
                {
                    size += 2;
                }
                else
                {
                    size += 1;
                }
            }
            return size;
        }

        /// @brief Get a snake_case char array from a string_view
        /// @tparam N Size of the output array, should match GetSnakeCaseSize(str)
        /// @param str String to convert to snake_case
        /// @return std::array of the converted string
        template <size_t N>
        constexpr std::array<char, N> ToSnakeCase(std::string_view str)
        {
            // We can't static_assert based on str, so throw instead
            if (GetSnakeCaseSize(str) != N)
            {
                throw std::invalid_argument("ToSnakeCase called with wrong output size");
            }
            std::array<char, N> output{};
            size_t index = 0;
            for (size_t i = 0; i < str.length(); ++i)
            {
                if (str[i] >= 'A' && str[i] <= 'Z')
                {
                    if (i > 0)
                    {
                        output[index++] = '_';
                    }
                    output[index++] = str[i] + 'a' - 'A';
                }
                else if (i > 0 && str[i] >= '0' && str[i] <= '9' && (str[i - 1] < '0' || str[i - 1] > '9'))
                {
                    output[index++] = '_';
                    output[index++] = str[i];
                }
                else
                {
                    output[index++] = str[i];
                }
            }
            return output;
        }

        /// @brief Convert a std::array of char to string_view
        /// @tparam N Size of the array
        /// @param a array to convert to string_view
        /// @return std::string_view wrapping around a chars
        template <size_t N>
        constexpr std::string_view ToStringView(const std::array<char, N>& a)
        {
            return std::string_view(a.data(), N);
        }

    }
}
