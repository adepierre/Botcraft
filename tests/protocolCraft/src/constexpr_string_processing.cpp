#include <catch2/catch_test_macros.hpp>

#include "protocolCraft/Utilities/ConstexprStrProcessing.hpp"
#include "protocolCraft/Utilities/Templates.hpp"

using namespace ProtocolCraft;

TEST_CASE("Get snake_case Size")
{
    static constexpr std::array<std::string_view, 8> test_strings = {
        "HelloWorld10", "hello", "Hello", "HelloWorld", "_", "1", "Hello1", "Hello10"
    };
    static constexpr std::array<size_t, 8> expected_sizes = {
        14, 5, 5, 11, 1, 1, 7, 8
    };
    Internal::loop<std::size(test_strings)>([&](auto i) {
        STATIC_REQUIRE(Internal::GetSnakeCaseSize(test_strings[i]) == expected_sizes[i]);
    });
}

TEST_CASE("To snake_case")
{
    static constexpr std::array<std::string_view, 8> test_strings = {
        "HelloWorld10", "hello", "Hello", "HelloWorld", "_", "1", "Hello1", "Hello10"
    };
    static constexpr std::array<std::string_view, 8> expected_strings = {
        "hello_world_10", "hello", "hello", "hello_world", "_", "1", "hello_1", "hello_10"
    };

    Internal::loop<std::size(test_strings)>([&](auto i) {
        static constexpr auto as_array = Internal::ToSnakeCase<Internal::GetSnakeCaseSize(test_strings[i])>(test_strings[i]);
        static constexpr std::string_view result = Internal::ToStringView<std::size(as_array)>(as_array);
        STATIC_REQUIRE(result == expected_strings[i]);
    });
}
