#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include "protocolCraft/NetworkType.hpp"
#if PROTOCOL_VERSION > 772 /* > 1.21.8 */
#include "protocolCraft/Types/LpVec3.hpp"

#include <array>
#endif

#if PROTOCOL_VERSION > 392 /* > 1.12.2 */
#include "protocolCraft/Types/Particles/Particle.hpp"
#include "protocolCraft/Types/Particles/DustParticleOption.hpp"
#endif

#if PROTOCOL_VERSION > 776 /* > 26.2 */
#include "protocolCraft/Types/PositionPath/PositionPath.hpp"
#include "protocolCraft/Types/PositionPath/PositionPathLinear.hpp"
#endif

#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
#include "protocolCraft/Types/Components/Subtypes/ConsumeEffects/ConsumeEffect.hpp"
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

namespace
{
    template <typename T>
    T RoundTrip(const T& in)
    {
        std::vector<unsigned char> bytes;
        WriteData<T>(in, bytes);
        ReadIterator iter = bytes.cbegin();
        size_t length = bytes.size();
        T out = ReadData<T>(iter, length);
        CHECK(length == 0);
        return out;
    }
}

TEST_CASE("Dynamic type")
{
#if PROTOCOL_VERSION > 392 /* > 1.12.2 */
    SECTION("Particle with options")
    {
        Particle p;
        p.SetParticleType(ParticleType::Dust);
        std::static_pointer_cast<DustParticleOption>(p.GetOption())->SetScale(2.0f);
        const Particle read = RoundTrip(p);
        CHECK(read.GetParticleType() == ParticleType::Dust);
        REQUIRE(std::dynamic_pointer_cast<DustParticleOption>(read.GetOption()) != nullptr);
        CHECK(std::static_pointer_cast<DustParticleOption>(read.GetOption())->GetScale() == 2.0f);
    }
#endif

#if PROTOCOL_VERSION > 776 /* > 26.2 */
    SECTION("PositionPath")
    {
        PositionPath path;
        path.SetType(PositionPathDataType::Linear);
        std::static_pointer_cast<PositionPathLinear>(path.GetData())->SetEndPosition({ 1.0, 2.0, 3.0 });
        const PositionPath read = RoundTrip(path);
        REQUIRE(read.GetType() == PositionPathDataType::Linear);
        CHECK(std::static_pointer_cast<PositionPathLinear>(read.GetData())->GetEndPosition() == std::array<double, 3>{ 1.0, 2.0, 3.0 });
    }
#endif

    SECTION("Payload never set")
    {
        SECTION("Particle")
        {
            RoundTrip(Particle());
        }
#if PROTOCOL_VERSION > 754 /* > 1.16.5 */
        SECTION("Vibration")
        {
            Particle vibration;
            vibration.SetParticleType(ParticleType::Vibration);
            RoundTrip(vibration);
        }
#endif
#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
        SECTION("Consume Effect")
        {
            RoundTrip(Components::ConsumeEffect());
        }
#endif
    }
}
