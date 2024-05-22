#include <catch2/catch_test_macros.hpp>

#include "protocolCraft/Utilities/ConstexprStrProcessing.hpp"

using namespace ProtocolCraft;

TEST_CASE("Split")
{
    SECTION("empty")
    {
        constexpr std::string_view test_str = "";
        constexpr auto splitted = Internal::SplitComma<0>(test_str);
        STATIC_REQUIRE(std::size(splitted) == 0);
    }

    SECTION("simple")
    {
        constexpr std::string_view test_str = "Hello";
        constexpr auto splitted = Internal::SplitComma<1>(test_str);
        STATIC_REQUIRE(std::size(splitted) == 1);
        STATIC_REQUIRE(splitted[0] == "Hello");
    }

    SECTION("space trimming")
    {
        constexpr std::string_view test_str = "   Hello        ";
        constexpr auto splitted = Internal::SplitComma<1>(test_str);
        STATIC_REQUIRE(std::size(splitted) == 1);
        STATIC_REQUIRE(splitted[0] == "Hello");
    }

    SECTION("complex")
    {
        constexpr std::string_view test_str = " Hello         , world    ,     !    ";
        constexpr auto splitted = Internal::SplitComma<3>(test_str);
        STATIC_REQUIRE(std::size(splitted) == 3);
        STATIC_REQUIRE(splitted[0] == "Hello");
        STATIC_REQUIRE(splitted[1] == "world");
        STATIC_REQUIRE(splitted[2] == "!");
    }
}

TEST_CASE("Get snake_case Size")
{
    static constexpr std::array<std::string_view, 4> test_strings = {
        "hello", "Hello", "HelloWorld", "_"
    };
    STATIC_REQUIRE(Internal::GetSnakeCaseSize(test_strings[0]) == 5);
    STATIC_REQUIRE(Internal::GetSnakeCaseSize(test_strings[1]) == 5);
    STATIC_REQUIRE(Internal::GetSnakeCaseSize(test_strings[2]) == 11);
    STATIC_REQUIRE(Internal::GetSnakeCaseSize(test_strings[3]) == 1);

    static constexpr std::array snake_case_size = Internal::GetSnakeCaseSize(test_strings);
    STATIC_REQUIRE(std::size(snake_case_size) == 4);
    STATIC_REQUIRE(snake_case_size[0] == 5);
    STATIC_REQUIRE(snake_case_size[1] == 5);
    STATIC_REQUIRE(snake_case_size[2] == 11);
    STATIC_REQUIRE(snake_case_size[3] == 1);
}

TEST_CASE("To snake_case")
{
    static constexpr std::array snake_case = Internal::ToSnakeCase<11>("HelloWorld");
    STATIC_REQUIRE(std::size(snake_case) == 11);
    STATIC_REQUIRE(snake_case[0] ==  'h');
    STATIC_REQUIRE(snake_case[1] ==  'e');
    STATIC_REQUIRE(snake_case[2] ==  'l');
    STATIC_REQUIRE(snake_case[3] ==  'l');
    STATIC_REQUIRE(snake_case[4] ==  'o');
    STATIC_REQUIRE(snake_case[5] ==  '_');
    STATIC_REQUIRE(snake_case[6] ==  'w');
    STATIC_REQUIRE(snake_case[7] ==  'o');
    STATIC_REQUIRE(snake_case[8] ==  'r');
    STATIC_REQUIRE(snake_case[9] ==  'l');
    STATIC_REQUIRE(snake_case[10] == 'd');

    static constexpr std::array<std::string_view, 4> test_strings = {
        "hello", "Hello", "HelloWorld", "_"
    };
    static constexpr std::array test_strings_size = Internal::GetSnakeCaseSize(test_strings);
    static constexpr std::tuple test_strings_tuple = Internal::ArrayToSnakeCaseTuple<std::size(test_strings), test_strings_size>(test_strings);
    static constexpr std::array test_strings_snake_case = Internal::TupleOfArraysToArrayOfStr(test_strings_tuple);

    STATIC_REQUIRE(std::size(test_strings_snake_case) == 4);
    STATIC_REQUIRE(test_strings_snake_case[0] == "hello");
    STATIC_REQUIRE(test_strings_snake_case[1] == "hello");
    STATIC_REQUIRE(test_strings_snake_case[2] == "hello_world");
    STATIC_REQUIRE(test_strings_snake_case[3] == "_");
}
