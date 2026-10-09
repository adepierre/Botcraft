#if PROTOCOL_VERSION > 764 /* > 1.20.2 */
#include <catch2/catch_test_macros.hpp>

#include <string>
#include <utility>
#include <vector>

#include "protocolCraft/BinaryReadWrite.hpp"
#include "protocolCraft/Types/Chat/Chat.hpp"

using namespace ProtocolCraft;

namespace
{
    // Parsing is only called when reading data from network
    // So serialize/deserialize to trigger the parsing
    std::string ParseText(const NBT::Tag& tag)
    {
        WriteContainer bytes;
        WriteData<NBT::Tag>(tag, bytes);
        ReadIterator iter = bytes.cbegin();
        size_t length = bytes.size();
        return ReadData<Chat>(iter, length).GetText();
    }
}

TEST_CASE("Plain text")
{
    SECTION("String")
    {
        const NBT::Tag t{ "hello" };
        CHECK(ParseText(t) == "hello");
    }

    SECTION("Simple compound")
    {
        const NBT::TagCompound c{ { "text", "hello" } };
        CHECK(ParseText(c) == "hello");
    }

    SECTION("String list")
    {
        const NBT::TagList l{ std::vector<std::string>{ ("hello"), NBT::TagString(", "), NBT::TagString("world") } };
        CHECK(ParseText(l) == "hello, world");
    }

    SECTION("Extra compound")
    {
        const NBT::TagCompound c = {
            { "text", NBT::TagString{"hello"} },
            { "extra", NBT::TagList{std::vector<NBT::TagCompound>{
                NBT::TagCompound{ { "text", ", " } },
                NBT::TagCompound{ { "text", "world"} }
            } } }
        };
        CHECK(ParseText(c) == "hello, world");
    }

    SECTION("Extra string")
    {
        const NBT::TagCompound c = {
            { "text", NBT::TagString{"hello"} },
            { "extra", NBT::TagList{std::vector<std::string>{
                ", ",
                "world"
            } } }
        };
        CHECK(ParseText(c) == "hello, world");
    }

    SECTION("Nested extra")
    {
        const NBT::TagCompound c = {
            { "text", NBT::TagString{"hello"} },
            { "extra", NBT::TagCompound{
                { "text", ", " },
                { "extra", "world" }
            } }
        };
        CHECK(ParseText(c) == "hello, world");
    }

    SECTION("Color")
    {
        const NBT::TagCompound c = {
            { "text", NBT::TagString{"hello"} },
            { "color", "red" }
        };
        CHECK(ParseText(c) == "hello");
    }
}

TEST_CASE("Translatable")
{
    SECTION("Fallback")
    {
        const NBT::TagCompound c = {
            { "translate", NBT::TagString{"translate.text.key"} },
            { "with", NBT::TagString{"world"} },
            { "fallback", NBT::TagString{"hello, %s"} },
        };
        CHECK(ParseText(c) == "hello, world");
    }

    SECTION("Positional args")
    {
        const NBT::TagCompound c = {
            { "translate", NBT::TagString{"translate.text.key"} },
            { "with", NBT::TagList{std::vector<std::string>{ "world", "hello" } } },
            { "fallback", NBT::TagString{"%2$s, %1$s"} },
        };
        CHECK(ParseText(c) == "hello, world");
    }

    SECTION("No fallback")
    {
        const NBT::TagCompound c = {
            { "translate", NBT::TagString{"translate.text.key"} },
            { "with", NBT::TagList{std::vector<std::string>{ "hello", "world" }}},
        };
        CHECK(ParseText(c) == "translate.text.key[hello, world]");
    }

    SECTION("Numeric args")
    {
        const NBT::TagCompound c = {
            { "translate", NBT::TagString{"translate.text.key"} },
            { "with", NBT::TagList{std::vector<int>{ 1, 2, 3 } } },
            { "fallback", NBT::TagString{"%s+%s=%s"} },
        };
        CHECK(ParseText(c) == "1+2=3");
    }

    SECTION("With extras")
    {
        const NBT::TagCompound c = {
            { "translate", NBT::TagString{"translate.text.key"} },
            { "with", NBT::TagCompound { { "text", NBT::TagString{"hello"} }, { "extra", NBT::TagString{", world"} } } },
            { "fallback", NBT::TagString{"[%s]"} },
        };
        CHECK(ParseText(c) == "[hello, world]");
    }

    SECTION("Mixed args")
    {
        const NBT::TagCompound c = {
            { "translate", NBT::TagString{"translate.text.key"} },
            { "with", NBT::TagList{std::vector<NBT::TagCompound>{
                NBT::TagCompound{ { "", 64 } },
                NBT::TagCompound{ { "text", "stone" } },
                NBT::TagCompound{ { "", "Steve" } }
            } } },
            { "fallback", NBT::TagString{"Gave %s %s to %s"} },
        };
        CHECK(ParseText(c) == "Gave 64 stone to Steve");
    }
}

TEST_CASE("Other types")
{
    SECTION("Keybind")
    {
        const NBT::TagCompound c{ { "keybind", "key.jump" } };
        CHECK(ParseText(c) == "key.jump");
    }

    SECTION("Selector")
    {
        const NBT::TagCompound c{ { "selector", "@e" } };
        CHECK(ParseText(c) == "@e");
    }

    SECTION("Player")
    {
        const NBT::TagCompound c{ { "player", "Steve" } };
        CHECK(ParseText(c) == "<Steve>");
    }

    SECTION("Sprite")
    {
        const NBT::TagCompound c = {
            { "object", NBT::TagCompound{ {"sprite", "minecraft:chest" } } },
            { "fallback", NBT::TagString{"[image]"} },
        };
        CHECK(ParseText(c) == "[image]");
    }
}
#endif
