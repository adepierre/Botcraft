#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#if PROTOCOL_VERSION > 772 /* > 1.21.8 */
#include "protocolCraft/Types/LpVec3.hpp"

#include <array>
#endif

using namespace ProtocolCraft;

#if PROTOCOL_VERSION > 772 /* > 1.21.8 */
TEST_CASE("LpVec3")
{
    const std::pair<std::array<double, 3>, std::vector<unsigned char>> vec3_and_serialized = GENERATE(
        std::pair<std::array<double, 3>, std::vector<unsigned char>>{ {  0.0,      0.0,      0.0 },      { 0x00 } },
        std::pair<std::array<double, 3>, std::vector<unsigned char>>{ {  1.0,      2.0,      3.0 },      { 0xA3, 0xAA, 0xFF, 0xFD, 0xAA, 0xA6 } },
        std::pair<std::array<double, 3>, std::vector<unsigned char>>{ {  0.5,      1.5,      2.5 },      { 0x53, 0x55, 0xEA, 0xA9, 0x7F, 0xFE } },
        std::pair<std::array<double, 3>, std::vector<unsigned char>>{ {  100000.0, 100000.0, 100000.0 }, { 0xF4, 0xFF, 0xFF, 0xFD, 0xFF, 0xFB, 0xA8, 0xC3, 0x01 } },
        std::pair<std::array<double, 3>, std::vector<unsigned char>>{ { -1.0,     -2.0,     -3.0 },      { 0x53, 0x55, 0x00, 0x00, 0x55, 0x55 } }
    );
    INFO("(" << vec3_and_serialized.first[0] << ", " << vec3_and_serialized.first[1] << ", " << vec3_and_serialized.first[2] << ")");

    LpVec3 lpvec3;
    lpvec3
        .SetX(vec3_and_serialized.first[0])
        .SetY(vec3_and_serialized.first[1])
        .SetZ(vec3_and_serialized.first[2]);
    std::vector<unsigned char> serialized;
    lpvec3.Write(serialized);
    CHECK(serialized.size() == vec3_and_serialized.second.size());
    CHECK(serialized == vec3_and_serialized.second);

    auto iter = vec3_and_serialized.second.begin();
    size_t length = vec3_and_serialized.second.size();
    LpVec3 reconstructed;
    reconstructed.Read(iter, length);

    CHECK_THAT(reconstructed.GetX(), Catch::Matchers::WithinAbs(vec3_and_serialized.first[0], 1e-3));
    CHECK_THAT(reconstructed.GetY(), Catch::Matchers::WithinAbs(vec3_and_serialized.first[1], 1e-3));
    CHECK_THAT(reconstructed.GetZ(), Catch::Matchers::WithinAbs(vec3_and_serialized.first[2], 1e-3));
}
#endif
