#pragma once

#include <array>
#include <stdexcept>
#include <string_view>
#include <tuple>

namespace ProtocolCraft
{
    namespace Internal
    {
        /// @brief Constexpr function to split a comma separated string into individual values
        /// @tparam N Number of values to extract from the string
        /// @param str Comma separated string
        /// @return Array of individual values
        template <size_t N>
        constexpr std::array<std::string_view, N> SplitComma(std::string_view str)
        {
            std::array<std::string_view, N> arr{};
            std::size_t start = 0, end = 0;

            for (std::size_t i = 0; i < N && end != std::string_view::npos; i++)
            {
                end = str.find_first_of(',', start);
                // Remove leading whitespaces
                while (str[start] == ' ' && start < end - 1)
                {
                    start += 1;
                }
                std::string_view sub = str.substr(start, end - start);
                // Remove trailing whitespaces
                size_t real_end = sub.find_last_not_of(' ');
                arr[i] = real_end == std::string_view::npos ? sub : sub.substr(0, real_end + 1);
                start = end + 1;
            }

            return arr;
        }

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

        template<size_t N, std::size_t... I>
        constexpr std::array<size_t, N> GetSnakeCaseSize(const std::array<std::string_view, N>& a, std::index_sequence<I...>)
        {
            return std::array{ GetSnakeCaseSize(a[I])... };
        }

        /// @brief Get a std::array of the snake_case length of each string in input array
        /// @tparam N N Size of the array
        /// @param a Array of strings to convert
        /// @return std::array, size of snake_case conversion for each string in a
        template<size_t N>
        constexpr std::array<size_t, N> GetSnakeCaseSize(const std::array<std::string_view, N>& a)
        {
            if constexpr (N == 0)
            {
                return {};
            }
            else
            {
                return GetSnakeCaseSize(a, std::make_index_sequence<N>{});
            }
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

        template <size_t N, const std::array<size_t, N>& lengths, std::size_t... Is>
        constexpr auto ArrayToSnakeCaseTuple(const std::array<std::string_view, N>& str, std::index_sequence<Is...>)
        {
            return std::make_tuple(ToSnakeCase<lengths[Is]>(str[Is])...);
        }

        /// @brief Convert an array of string_view to a tuple of snake_case char arrays
        /// @tparam N Number of strings in the input array
        /// @tparam lengths Size of the converted string for each string in the input array
        /// @param str strings to convert
        /// @return A std::tuple of std::array containing the converted strings
        template <size_t N, const std::array<size_t, N>& lengths>
        constexpr auto ArrayToSnakeCaseTuple(const std::array<std::string_view, N>& str)
        {
            return ArrayToSnakeCaseTuple<N, lengths>(str, std::make_index_sequence<N>{});
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

        template <typename Tuple, std::size_t... I>
        constexpr std::array<std::string_view, std::tuple_size_v<Tuple>> TupleOfArraysToArrayOfStr(const Tuple& t, std::index_sequence<I...>)
        {
            return { ToStringView(std::get<I>(t)) ... };
        }
        /// @brief Create an array of string_view from a tuple of char arrays
        /// @tparam Tuple A std::tuple of std::array<char>
        /// @param t a Tuple instance containing all the std::arrays
        /// @return An array of std::string_view wrapping each Tuple char arrays
        template <typename Tuple>
        constexpr auto TupleOfArraysToArrayOfStr(const Tuple& t)
        {
            return TupleOfArraysToArrayOfStr(t, std::make_index_sequence<std::tuple_size_v<Tuple>>{});
        }
    }
}
