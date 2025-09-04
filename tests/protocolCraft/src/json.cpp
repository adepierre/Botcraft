#include <catch2/catch_test_macros.hpp>

#include <deque>
#include <list>

#include "protocolCraft/Utilities/Json.hpp"

using namespace ProtocolCraft;

TEST_CASE("Constructors and is")
{
    Json::Value j;

    SECTION("empty")
    {
        CHECK(j.is<std::monostate>());
    }

    SECTION("Object")
    {
        j = Json::Object();
        CHECK(j.is<Json::Object>());
    }

    SECTION("Array")
    {
        j = Json::Array();
        CHECK(j.is<Json::Array>());

        j = std::vector<int>(4, 0);
        CHECK(j.is<Json::Array>());

        j = std::array<int, 4>();
        CHECK(j.is<Json::Array>());

        j = std::array<Json::Object, 4>();
        CHECK(j.is<Json::Array>());
    }

    SECTION("std::string")
    {
        j = "s";
        CHECK(j.is<std::string>());

        j = std::string();
        CHECK(j.is<std::string>());
    }

    SECTION("bool")
    {
        j = true;
        CHECK(j.is<bool>());

        j = false;
        CHECK(j.is<bool>());
    }

    SECTION("long long int")
    {
        j = 3LL;
        CHECK(j.is<long long int>());

        j = -3LL;
        CHECK(j.is<long long int>());

        j = 3;
        CHECK(j.is<long long int>());

        j = static_cast<short>(3);
        CHECK(j.is<long long int>());

        j = static_cast<char>(3);
        CHECK(j.is<long long int>());

        enum class TestEnum
        {
            A = 1,
            B = 2
        };

        j = TestEnum::A;
        CHECK(j.is<long long int>());
    }

    SECTION("unsigned long long int")
    {
        j = 3ULL;
        CHECK(j.is<unsigned long long int>());

        j = 3U;
        CHECK(j.is<unsigned long long int>());

        j = static_cast<unsigned short>(3);
        CHECK(j.is<unsigned long long int>());

        j = static_cast<unsigned char>(3);
        CHECK(j.is<unsigned long long int>());
    }

    SECTION("double")
    {
        j = 3.14;
        CHECK(j.is<double>());

        j = -3.14;
        CHECK(j.is<double>());

        j = 3.14f;
        CHECK(j.is<double>());

        j = -3.14f;
        CHECK(j.is<double>());
    }

    SECTION("is_integer")
    {
        j = 3LL;
        CHECK(j.is_integer());

        j = 3ULL;
        CHECK(j.is_integer());

        j = 3;
        CHECK(j.is_integer());

        j = 3.1;
        CHECK_FALSE(j.is_integer());

        j = 3.1f;
        CHECK_FALSE(j.is_integer());

        j = "a";
        CHECK_FALSE(j.is_integer());

        j = true;
        CHECK_FALSE(j.is_integer());
    }

    SECTION("is_number")
    {
        j = 3LL;
        CHECK(j.is_number());

        j = 3ULL;
        CHECK(j.is_number());

        j = 3;
        CHECK(j.is_number());

        j = 3.1;
        CHECK(j.is_number());

        j = 3.1f;
        CHECK(j.is_number());

        j = "a";
        CHECK_FALSE(j.is_number());

        j = true;
        CHECK_FALSE(j.is_number());
    }
}

TEST_CASE("size()")
{
    Json::Value j;

    SECTION("empty")
    {
        CHECK(j.size() == 0);
    }

    SECTION("Object")
    {
        j = Json::Object();
        CHECK(j.size() == 0);
    }

    SECTION("Array")
    {
        j = Json::Array();
        CHECK(j.size() == 0);

        j = std::vector<int>(4, 0);
        CHECK(j.size() == 4);
    }

    SECTION("std::string")
    {
        j = "s";
        CHECK_THROWS(j.size());
    }

    SECTION("bool")
    {
        j = true;
        CHECK_THROWS(j.size());
    }

    SECTION("long long int")
    {
        j = 3LL;
        CHECK_THROWS(j.size());
    }

    SECTION("unsigned long long int")
    {
        j = 3ULL;
        CHECK_THROWS(j.size());
    }

    SECTION("double")
    {
        j = 3.14;
        CHECK_THROWS(j.size());
    }
}

TEST_CASE("get")
{
    Json::Value j;

    SECTION("empty")
    {
        CHECK_THROWS(j.get<bool>());
        CHECK_THROWS(j.get<Json::Object>());
        CHECK_THROWS(j.get<Json::Array>());
        CHECK_THROWS(j.get<long long int>());
        CHECK_THROWS(j.get<unsigned long long int>());
        CHECK_THROWS(j.get<std::string>());
        CHECK_THROWS(j.get<char>());
        CHECK_THROWS(j.get<double>());
        CHECK_THROWS(j.get<float>());
    }

    SECTION("Object")
    {
        j = { {"a", 1}, {"b", 2} };
        CHECK_THROWS(j.get<bool>());
        CHECK_NOTHROW(j.get<Json::Object>());
        CHECK_THROWS(j.get<Json::Array>());
        CHECK_THROWS(j.get<long long int>());
        CHECK_THROWS(j.get<unsigned long long int>());
        CHECK_THROWS(j.get<std::string>());
        CHECK_THROWS(j.get<char>());
        CHECK_THROWS(j.get<double>());
        CHECK_THROWS(j.get<float>());

        CHECK(j.get<Json::Object>().size() == 2);
        j.get<Json::Object>()["c"] = 3;
        CHECK(j.get<Json::Object>().size() == 3);
    }

    SECTION("Array")
    {
        j = { 1,2,3 };
        CHECK_THROWS(j.get<bool>());
        CHECK_THROWS(j.get<Json::Object>());
        CHECK_NOTHROW(j.get<Json::Array>());
        CHECK_THROWS(j.get<long long int>());
        CHECK_THROWS(j.get<unsigned long long int>());
        CHECK_THROWS(j.get<std::string>());
        CHECK_THROWS(j.get<char>());
        CHECK_THROWS(j.get<double>());
        CHECK_THROWS(j.get<float>());

        CHECK(j.get<Json::Array>().size() == 3);
        j.get<Json::Array>().push_back(3);
        CHECK(j.get<Json::Array>().size() == 4);
    }

    SECTION("std::string")
    {
        j = "Hello";
        CHECK_THROWS(j.get<bool>());
        CHECK_THROWS(j.get<Json::Object>());
        CHECK_THROWS(j.get<Json::Array>());
        CHECK_THROWS(j.get<long long int>());
        CHECK_THROWS(j.get<unsigned long long int>());
        CHECK_NOTHROW(j.get<std::string>());
        CHECK_THROWS(j.get<char>());
        CHECK_THROWS(j.get<double>());
        CHECK_THROWS(j.get<float>());

        CHECK(j.get<std::string>() == "Hello");
        j.get<std::string>() += " world!";
        CHECK(j.get<std::string>() == "Hello world!");
    }

    SECTION("bool")
    {
        j = true;
        CHECK_NOTHROW(j.get<bool>());
        CHECK_THROWS(j.get<Json::Object>());
        CHECK_THROWS(j.get<Json::Array>());
        CHECK_THROWS(j.get<long long int>());
        CHECK_THROWS(j.get<unsigned long long int>());
        CHECK_THROWS(j.get<std::string>());
        CHECK_THROWS(j.get<char>());
        CHECK_THROWS(j.get<double>());
        CHECK_THROWS(j.get<float>());

        CHECK(j.get<bool>() == true);
    }

    SECTION("long long int")
    {
        j = -1;
        CHECK_THROWS(j.get<bool>());
        CHECK_THROWS(j.get<Json::Object>());
        CHECK_THROWS(j.get<Json::Array>());
        CHECK_NOTHROW(j.get<long long int>());
        CHECK_NOTHROW(j.get<unsigned long long int>());
        CHECK_THROWS(j.get<std::string>());
        CHECK_NOTHROW(j.get<char>());
        CHECK_NOTHROW(j.get<double>());
        CHECK_NOTHROW(j.get<float>());

        CHECK(j.get<long long int>() == -1LL);
        CHECK(j.get<int>() == -1);
        CHECK(j.get<unsigned int>() == static_cast<unsigned int>(-1));
        CHECK(j.get<double>() == -1.0);
    }

    SECTION("unsigned long long int")
    {
        j = 1U;
        CHECK_THROWS(j.get<bool>());
        CHECK_THROWS(j.get<Json::Object>());
        CHECK_THROWS(j.get<Json::Array>());
        CHECK_NOTHROW(j.get<long long int>());
        CHECK_NOTHROW(j.get<unsigned long long int>());
        CHECK_THROWS(j.get<std::string>());
        CHECK_NOTHROW(j.get<char>());
        CHECK_NOTHROW(j.get<double>());
        CHECK_NOTHROW(j.get<float>());

        CHECK(j.get<unsigned long long int>() == 1U);
        CHECK(j.get<unsigned int>() == 1U);
        CHECK(j.get<int>() == 1);
        CHECK(j.get<double>() == 1.0);
    }

    SECTION("double")
    {
        j = 1.0;
        CHECK_THROWS(j.get<bool>());
        CHECK_THROWS(j.get<Json::Object>());
        CHECK_THROWS(j.get<Json::Array>());
        CHECK_NOTHROW(j.get<long long int>());
        CHECK_NOTHROW(j.get<unsigned long long int>());
        CHECK_THROWS(j.get<std::string>());
        CHECK_NOTHROW(j.get<char>());
        CHECK_NOTHROW(j.get<double>());
        CHECK_NOTHROW(j.get<float>());

        CHECK(j.get<double>() == 1.0);
        CHECK(j.get<float>() == 1.0);
        CHECK(j.get<char>() == 1);
    }

    SECTION("get_number")
    {
        j = 1.0;
        CHECK(j.get_number<double>() == 1.0);
        CHECK(j.get_number<int>() == 1);

        j = 1ULL;
        CHECK(j.get_number<double>() == 1.0);
        CHECK(j.get_number<unsigned long long int>() == 1);

        j = 1LL;
        CHECK(j.get_number<double>() == 1.0);
        CHECK(j.get_number<long long int>() == 1);

        j = true;
        CHECK_THROWS(j.get_number<double>());
        CHECK_THROWS(j.get_number<unsigned long long int>());
    }
}

TEST_CASE("Array")
{
    Json::Value j;
    SECTION("push_back")
    {
        j.push_back("foo");
        j.push_back(1);
        j.push_back(true);
        CHECK(j.is<Json::Array>());
        CHECK(j.size() == 3);
        CHECK(j[2].get<bool>() == true);
    }

    SECTION("initializer list")
    {
        j = { "foo", 1, true };
        CHECK(j.is<Json::Array>());
        CHECK(j.size() == 3);
        CHECK(j[2].get<bool>() == true);
    }

    SECTION("from std::vector")
    {
        j = std::vector<int>({ 1,2,3 });
        CHECK(j.is<Json::Array>());
        CHECK(j.size() == 3);
        CHECK(j[2].get<int>() == 3);
    }

    SECTION("from std::deque")
    {
        j = std::deque<int>({ 1,2,3 });
        CHECK(j.is<Json::Array>());
        CHECK(j.size() == 3);
        CHECK(j[2].get<int>() == 3);
    }

    SECTION("from std::list")
    {
        j = std::list<int>({ 1,2,3 });
        CHECK(j.is<Json::Array>());
        CHECK(j.size() == 3);
        CHECK(j[2].get<int>() == 3);
    }
}

TEST_CASE("Object")
{
    Json::Value j;

    SECTION("Cast from empty")
    {
        j["pi"] = 3.141;
        j["happy"] = true;
        j["name"] = "Niels";
        j["nothing"] = nullptr;
        j["answer"]["everything"] = 42;
        j["list"] = { 1, 0, 2 };
        j["object"] = { {"currency", "USD"}, {"value", 42.99} };

        CHECK(j.is<Json::Object>());
        CHECK(j.size() == 7);
        CHECK(j["happy"].is<bool>());
        CHECK(j["name"].is<std::string>());
        CHECK(j["nothing"].is<std::monostate>());
        CHECK(j["answer"].is<Json::Object>());
        CHECK(j["answer"].size() == 1);
        CHECK(j["answer"]["everything"].is<long long int>());
        CHECK(j["answer"]["everything"].get<long long int>() == 42);
        CHECK(j["list"].is<Json::Array>());
        CHECK(j["list"].size() == 3);
        CHECK(j["object"].is<Json::Object>());
        CHECK(j["object"].size() == 2);
    }

    SECTION("initializer list")
    {
        j =
        {
            {"pi", 3.141},
            {"happy", true},
            {"name", "Niels"},
            {"nothing", nullptr},
            {
                "answer", {
                    {"everything", 42}
                }
            },
            {"list", {1, 0, 2}},
            {
                "object", {
                    {"currency", "USD"},
                    {"value", 42.99}
                }
            }
        };

        CHECK(j.is<Json::Object>());
        CHECK(j.size() == 7);
        CHECK(j["happy"].is<bool>());
        CHECK(j["name"].is<std::string>());
        CHECK(j["nothing"].is<std::monostate>());
        CHECK(j["answer"].is<Json::Object>());
        CHECK(j["answer"].size() == 1);
        CHECK(j["answer"]["everything"].is<long long int>());
        CHECK(j["answer"]["everything"].get<long long int>() == 42);
        CHECK(j["list"].is<Json::Array>());
        CHECK(j["list"].size() == 3);
        CHECK(j["object"].is<Json::Object>());
        CHECK(j["object"].size() == 2);
    }
}

TEST_CASE("Dump")
{
    Json::Value j;

    SECTION("Null")
    {
        j = { };
        CHECK(j.Dump() == "null");
        CHECK(j.Dump(0) == "null");
        CHECK(j.Dump(4) == "null");
        CHECK(j.Dump(1, '\t') == "null");

        j = nullptr;
        CHECK(j.Dump() == "null");
        CHECK(j.Dump(0) == "null");
        CHECK(j.Dump(4) == "null");
        CHECK(j.Dump(1, '\t') == "null");
    }

    SECTION("String")
    {
        j = "";
        CHECK(j.Dump() == "\"\"");
        CHECK(j.Dump(0) == "\"\"");
        CHECK(j.Dump(4) == "\"\"");
        CHECK(j.Dump(1, '\t') == "\"\"");

        j = "hello, \"world\"!";
        CHECK(j.Dump() == "\"hello, \\\"world\\\"!\"");
        CHECK(j.Dump(0) == "\"hello, \\\"world\\\"!\"");
        CHECK(j.Dump(4) == "\"hello, \\\"world\\\"!\"");
        CHECK(j.Dump(1, '\t') == "\"hello, \\\"world\\\"!\"");

        j = "\"\n\"";
        CHECK(j.Dump() == "\"\\\"\\n\\\"\"");
        CHECK(j.Dump(0) == "\"\\\"\\n\\\"\"");
        CHECK(j.Dump(4) == "\"\\\"\\n\\\"\"");
        CHECK(j.Dump(1, '\t') == "\"\\\"\\n\\\"\"");
    }

    SECTION("Bool")
    {
        j = true;
        CHECK(j.Dump() == "true");
        CHECK(j.Dump(0) == "true");
        CHECK(j.Dump(4) == "true");
        CHECK(j.Dump(1, '\t') == "true");

        j = false;
        CHECK(j.Dump() == "false");
        CHECK(j.Dump(0) == "false");
        CHECK(j.Dump(4) == "false");
        CHECK(j.Dump(1, '\t') == "false");
    }

    SECTION("Int")
    {
        j = 1;
        CHECK(j.Dump() == "1");
        CHECK(j.Dump(0) == "1");
        CHECK(j.Dump(4) == "1");
        CHECK(j.Dump(1, '\t') == "1");

        j = std::numeric_limits<long long int>::max();
        CHECK(j.Dump() == std::to_string(std::numeric_limits<long long int>::max()));
        CHECK(j.Dump(0) == std::to_string(std::numeric_limits<long long int>::max()));
        CHECK(j.Dump(4) == std::to_string(std::numeric_limits<long long int>::max()));
        CHECK(j.Dump(1, '\t') == std::to_string(std::numeric_limits<long long int>::max()));

        j = std::numeric_limits<long long int>::min();
        CHECK(j.Dump() == std::to_string(std::numeric_limits<long long int>::min()));
        CHECK(j.Dump(0) == std::to_string(std::numeric_limits<long long int>::min()));
        CHECK(j.Dump(4) == std::to_string(std::numeric_limits<long long int>::min()));
        CHECK(j.Dump(1, '\t') == std::to_string(std::numeric_limits<long long int>::min()));
    }

    SECTION("UInt")
    {
        j = 1u;
        CHECK(j.Dump() == "1");
        CHECK(j.Dump(0) == "1");
        CHECK(j.Dump(4) == "1");
        CHECK(j.Dump(1, '\t') == "1");

        j = std::numeric_limits<unsigned long long int>::max();
        CHECK(j.Dump() == std::to_string(std::numeric_limits<unsigned long long int>::max()));
        CHECK(j.Dump(0) == std::to_string(std::numeric_limits<unsigned long long int>::max()));
        CHECK(j.Dump(4) == std::to_string(std::numeric_limits<unsigned long long int>::max()));
        CHECK(j.Dump(1, '\t') == std::to_string(std::numeric_limits<unsigned long long int>::max()));
    }

    SECTION("Double")
    {
        j = 1.0;
        CHECK(j.Dump() == "1.0");
        CHECK(j.Dump(0) == "1.0");
        CHECK(j.Dump(4) == "1.0");
        CHECK(j.Dump(1, '\t') == "1.0");

        j = -1.0;
        CHECK(j.Dump() == "-1.0");
        CHECK(j.Dump(0) == "-1.0");
        CHECK(j.Dump(4) == "-1.0");
        CHECK(j.Dump(1, '\t') == "-1.0");
    }

    SECTION("Array")
    {
        j = Json::Array();
        CHECK(j.Dump() == "[]");
        CHECK(j.Dump(0) == "[]");
        CHECK(j.Dump(4) == "[]");
        CHECK(j.Dump(4, '\t') == "[]");

        j = { "a", 1, true, 2.0, { {}, nullptr} };
        CHECK(j.Dump() == "[\"a\",1,true,2.0,[null,null]]");
        CHECK(j.Dump(0) ==
            "[\n"
            "\"a\",\n"
            "1,\n"
            "true,\n"
            "2.0,\n"
            "[\n"
            "null,\n"
            "null\n"
            "]\n"
            "]");
        CHECK(j.Dump(4) ==
            "[\n"
            "    \"a\",\n"
            "    1,\n"
            "    true,\n"
            "    2.0,\n"
            "    [\n"
            "        null,\n"
            "        null\n"
            "    ]\n"
            "]");
        CHECK(j.Dump(1, '\t') ==
            "[\n"
            "\t\"a\",\n"
            "\t1,\n"
            "\ttrue,\n"
            "\t2.0,\n"
            "\t[\n"
            "\t\tnull,\n"
            "\t\tnull\n"
            "\t]\n"
            "]"
        );
    }

    SECTION("Object")
    {
        j = Json::Object();
        CHECK(j.Dump() == "{}");
        CHECK(j.Dump(0) == "{}");
        CHECK(j.Dump(4) == "{}");
        CHECK(j.Dump(1, '\t') == "{}");

        j = { { "a", { "b", 1 } }, { "c", "hello"} };
        CHECK(j.Dump() == "{\"a\":{\"b\":1},\"c\":\"hello\"}");
        CHECK(j.Dump(0) ==
            "{\n"
            "\"a\": {\n"
            "\"b\": 1\n"
            "},\n"
            "\"c\": \"hello\"\n"
            "}"
        );
        CHECK(j.Dump(4) ==
            "{\n"
            "    \"a\": {\n"
            "        \"b\": 1\n"
            "    },\n"
            "    \"c\": \"hello\"\n"
            "}"
        );
        CHECK(j.Dump(1, '\t') ==
            "{\n"
            "\t\"a\": {\n"
            "\t\t\"b\": 1\n"
            "\t},\n"
            "\t\"c\": \"hello\"\n"
            "}"
        );
    }
}

TEST_CASE("Parse")
{
    std::string s;
    Json::Value result;

    SECTION("Empty")
    {
        s = "null";
        result = Json::Parse(s);
        CHECK(result.is<std::monostate>());
    }

    SECTION("Bool")
    {
        s = "true";
        result = Json::Parse(s);
        CHECK(result.is<bool>());
        CHECK(result.get<bool>() == true);

        s = "false";
        result = Json::Parse(s);
        CHECK(result.is<bool>());
        CHECK(result.get<bool>() == false);
    }

    SECTION("String")
    {
        s = "\"\"";
        result = Json::Parse(s);
        CHECK(result.is<std::string>());
        CHECK(result.get<std::string>() == "");

        s = "\"hello\"";
        result = Json::Parse(s);
        CHECK(result.is<std::string>());
        CHECK(result.get<std::string>() == "hello");

        s = "\"hel\\\"lo\"";
        result = Json::Parse(s);
        CHECK(result.is<std::string>());
        CHECK(result.get<std::string>() == "hel\\\"lo");

        s = "\"\\u000a\"";
        result = Json::Parse(s);
        CHECK(result.is<std::string>());
        CHECK(result.get<std::string>() == "\n");

        s = "\"\\u000A\"";
        result = Json::Parse(s);
        CHECK(result.is<std::string>());
        CHECK(result.get<std::string>() == "\n");

        s = "\"\\u0009\"";
        result = Json::Parse(s);
        CHECK(result.is<std::string>());
        CHECK(result.get<std::string>() == "\t");

        s = "\"\\u12\"";
        CHECK_THROWS(Json::Parse(s));

        s = "\"\t\"";
        CHECK_THROWS(Json::Parse(s));

        s = "\"\n\"";
        CHECK_THROWS(Json::Parse(s));

        s = "\"\r\"";
        CHECK_THROWS(Json::Parse(s));

        s = "\"\b\"";
        CHECK_THROWS(Json::Parse(s));

        s = "\"\f\"";
        CHECK_THROWS(Json::Parse(s));
    }

    SECTION("Number")
    {
        s = "0.1";
        result = Json::Parse(s);
        CHECK(result.is<double>());
        CHECK(result.get<double>() == 0.1);

        s = "147e12";
        result = Json::Parse(s);
        CHECK(result.is<double>());
        CHECK(result.get<double>() == 147e12);

        s = "147E+12";
        result = Json::Parse(s);
        CHECK(result.is<double>());
        CHECK(result.get<double>() == 147e12);

        s = "-147E-12";
        result = Json::Parse(s);
        CHECK(result.is<double>());
        CHECK(result.get<double>() == -147e-12);

        s = "1";
        result = Json::Parse(s);
        CHECK(result.is_integer());
        CHECK(result.is<unsigned long long int>());
        CHECK(result.get<unsigned long long int>() == 1);

        s = "9";
        result = Json::Parse(s);
        CHECK(result.is_integer());
        CHECK(result.is<unsigned long long int>());
        CHECK(result.get<unsigned long long int>() == 9);

        s = "-1";
        result = Json::Parse(s);
        CHECK(result.is_integer());
        CHECK(result.is<long long int>());
        CHECK(result.get<long long int>() == -1);

        s = "-99";
        result = Json::Parse(s);
        CHECK(result.is_integer());
        CHECK(result.is<long long int>());
        CHECK(result.get<long long int>() == -99);

        s = "0e+1";
        result = Json::Parse(s);
        CHECK(result.is<double>());
        CHECK(result.get<double>() == 0.0);

        s = "-0.000000000000000000000000000000000000000000000000000000000000000000000000000001";
        result = Json::Parse(s);
        CHECK(result.is<double>());
        CHECK(result.get<double>() == -0.000000000000000000000000000000000000000000000000000000000000000000000000000001);

        s = "5708990770823839207320493820740630171355185152";
        result = Json::Parse(s);
        CHECK(result.is<double>());
        CHECK(result.get<double>() == 5.7089907708238395e+45);

        s = "+1";
        CHECK_THROWS(Json::Parse(s));

        s = "0";
        result = Json::Parse(s);
        CHECK(result.is<unsigned long long int>());
        CHECK(result.get<unsigned long long int>() == 0);

        s = "007";
        CHECK_THROWS(Json::Parse(s));

        s = "1e";
        CHECK_THROWS(Json::Parse(s));

        s = "-01";
        CHECK_THROWS(Json::Parse(s));

        s = "0.e1";
        CHECK_THROWS(Json::Parse(s));

        s = "1+2";
        CHECK_THROWS(Json::Parse(s));

        s = "1e+-2";
        CHECK_THROWS(Json::Parse(s));

        s = "-.1";
        CHECK_THROWS(Json::Parse(s));

        s = "2.e1";
        CHECK_THROWS(Json::Parse(s));
    }

    SECTION("Array")
    {
        s = "[]";
        result = Json::Parse(s);
        CHECK(result.is<Json::Array>());
        CHECK(result.size() == 0);

        s = "[]\n";
        result = Json::Parse(s);
        CHECK(result.is<Json::Array>());
        CHECK(result.size() == 0);

        s = "[ ]";
        result = Json::Parse(s);
        CHECK(result.is<Json::Array>());
        CHECK(result.size() == 0);

        s = "[  \t  ]";
        result = Json::Parse(s);
        CHECK(result.is<Json::Array>());
        CHECK(result.size() == 0);

        s = "[1,\t2,3.0,4  ,\n 5,\"hello\"]";
        result = Json::Parse(s);
        CHECK(result.is<Json::Array>());
        CHECK(result.size() == 6);
        CHECK(result[5].get<std::string>() == "hello");

        s = "[,]";
        CHECK_THROWS(Json::Parse(s));

        s = "[1,2,]";
        CHECK_THROWS(Json::Parse(s));
    }

    SECTION("Object")
    {
        s = "{}";
        result = Json::Parse(s);
        CHECK(result.is<Json::Object>());
        CHECK(result.size() == 0);

        s = "{}\n";
        result = Json::Parse(s);
        CHECK(result.is<Json::Object>());
        CHECK(result.size() == 0);

        s = "{ }";
        result = Json::Parse(s);
        CHECK(result.is<Json::Object>());
        CHECK(result.size() == 0);

        s = "{ }";
        result = Json::Parse(s);
        CHECK(result.is<Json::Object>());
        CHECK(result.size() == 0);

        s = "{\"a\": 1,        \"b\":    42.0, \"c\": \t\t\t\"hello\",\n\n    \"d\": [1,2,3,\"world\"]\n\n\n}";
        result = Json::Parse(s);
        CHECK(result.is<Json::Object>());
        CHECK(result.size() == 4);
        CHECK(result["d"][3].get<std::string>() == "world");

        s = "{}more content";
        CHECK_THROWS(Json::Parse(s));

        s = "{,}";
        CHECK_THROWS(Json::Parse(s));

        s = "{\"a\": 1, }";
        CHECK_THROWS(Json::Parse(s));

        s = "{\"a\": 1, }";
        CHECK_NOTHROW(Json::Parse(s, true));
        CHECK(Json::Parse(s, true).is<std::monostate>());
    }
}

TEST_CASE("ToJsonAndBack")
{
    std::string input;

    input = "null";
    CHECK(input == Json::Parse(input).Dump());

    input = "2.0";
    CHECK(input == Json::Parse(input).Dump());

    input = "[\"a\",1,{\"b\":\"c\"}]";
    CHECK(input == Json::Parse(input).Dump());

    input = "{}";
    CHECK(input == Json::Parse(input).Dump());
}
