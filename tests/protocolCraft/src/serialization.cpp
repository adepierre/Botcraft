#include <catch2/catch_test_macros.hpp>

#include "protocolCraft/BinaryReadWrite.hpp"

using namespace ProtocolCraft;

TEST_CASE("Simple types")
{
    SECTION("bool")
    {
        std::vector<unsigned char> data = { 0x00, 0x01 };
        ReadIterator iter = data.cbegin();
        size_t length = data.size();

        const bool b1 = ReadData<bool>(iter, length);
        const bool b2 = ReadData<bool>(iter, length);

        REQUIRE(b1 == false);
        REQUIRE(b2 == true);

        std::vector<unsigned char> container1;
        WriteData<bool>(b1, container1);
        REQUIRE(container1.size() == 1);
        REQUIRE(container1[0] == 0x00);

        std::vector<unsigned char> container2;
        WriteData<bool>(b2, container2);
        REQUIRE(container2.size() == 1);
        REQUIRE(container2[0] == 0x01);
    }

    SECTION("int")
    {
        std::vector<unsigned char> data = { 0x00, 0x00, 0x00, 0x2A };
        ReadIterator iter = data.cbegin();
        size_t length = data.size();

        const int i = ReadData<int>(iter, length);

        REQUIRE(i == 42);

        std::vector<unsigned char> container;
        WriteData<int>(i, container);
        REQUIRE(container == data);
    }

    SECTION("float")
    {
        std::vector<unsigned char> data = { 0x42, 0x28, 0x00, 0x00 };
        ReadIterator iter = data.cbegin();
        size_t length = data.size();

        const float f = ReadData<float>(iter, length);

        REQUIRE(f == 42.0f);

        std::vector<unsigned char> container;
        WriteData<float>(f, container);
        REQUIRE(container == data);
    }
}

TEST_CASE("VarType")
{
    SECTION("VarInt")
    {
        std::vector<int> values = { 0, 1, 2, 127, 128, 255, 25565, 2097151, 2147483647, -1 };
        std::vector<std::vector<unsigned char>> bytes = {
            { 0x00 },
            { 0x01 },
            { 0x02 },
            { 0x7F },
            { 0x80, 0x01 },
            { 0xFF, 0x01 },
            { 0xDD, 0xC7, 0x01 },
            { 0xFF, 0xFF, 0x7F },
            { 0xFF, 0xFF, 0xFF, 0xFF, 0x07 },
            { 0xFF, 0xFF, 0xFF, 0xFF, 0x0F }
        };

        for (int i = 0; i < values.size(); ++i)
        {
            INFO("Value=" << values[i]);
            ReadIterator iter = bytes[i].cbegin();
            size_t length = bytes[i].size();
            const int v = ReadData<VarInt>(iter, length);
            REQUIRE(v == values[i]);

            std::vector<unsigned char> container;
            WriteData<VarInt>(v, container);
            REQUIRE(container == bytes[i]);
        }
    }

    SECTION("VarLong")
    {
        std::vector<long long int> values = { 0LL, 1LL, 2LL, 127LL, 128LL, 255LL, 2147483647LL, 9223372036854775807LL, -1LL, -2147483648LL };
        std::vector<std::vector<unsigned char>> bytes = {
            { 0x00 },
            { 0x01 },
            { 0x02 },
            { 0x7F },
            { 0x80, 0x01 },
            { 0xFF, 0x01 },
            { 0xFF, 0xFF, 0xFF, 0xFF, 0x07 },
            { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F },
            { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x01 },
            { 0x80, 0x80, 0x80, 0x80, 0xF8, 0xFF, 0xFF, 0xFF, 0xFF, 0x01 },
        };

        for (int i = 0; i < values.size(); ++i)
        {
            INFO("Value=" << values[i]);
            ReadIterator iter = bytes[i].cbegin();
            size_t length = bytes[i].size();
            const long long int v = ReadData<VarLong>(iter, length);
            REQUIRE(v == values[i]);

            std::vector<unsigned char> container;
            WriteData<VarLong>(v, container);
            REQUIRE(container == bytes[i]);
        }
    }
}
