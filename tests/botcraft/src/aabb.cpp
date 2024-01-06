#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include <catch2/generators/catch_generators.hpp>

#include <botcraft/Game/AABB.hpp>

using namespace Botcraft;

TEST_CASE("Constructor")
{
    AABB aabb(Vector3<double>(0.5, 0.5, 0.5), Vector3<double>(0.5, 0.5, 0.5));

    REQUIRE_THAT(aabb.GetMin().x, Catch::Matchers::WithinAbs(0.0, 1e-8));
    REQUIRE_THAT(aabb.GetMin().y, Catch::Matchers::WithinAbs(0.0, 1e-8));
    REQUIRE_THAT(aabb.GetMin().z, Catch::Matchers::WithinAbs(0.0, 1e-8));
    REQUIRE_THAT(aabb.GetMax().x, Catch::Matchers::WithinAbs(1.0, 1e-8));
    REQUIRE_THAT(aabb.GetMax().y, Catch::Matchers::WithinAbs(1.0, 1e-8));
    REQUIRE_THAT(aabb.GetMax().z, Catch::Matchers::WithinAbs(1.0, 1e-8));
}

TEST_CASE("Translate")
{
    AABB aabb(Vector3<double>(0.5, 0.5, 0.5), Vector3<double>(0.5, 0.5, 0.5));
    aabb.Translate(Vector3<double>(1.0, 1.0, 1.0));

    REQUIRE_THAT(aabb.GetMin().x, Catch::Matchers::WithinAbs(1.0, 1e-8));
    REQUIRE_THAT(aabb.GetMin().y, Catch::Matchers::WithinAbs(1.0, 1e-8));
    REQUIRE_THAT(aabb.GetMin().z, Catch::Matchers::WithinAbs(1.0, 1e-8));
    REQUIRE_THAT(aabb.GetMax().x, Catch::Matchers::WithinAbs(2.0, 1e-8));
    REQUIRE_THAT(aabb.GetMax().y, Catch::Matchers::WithinAbs(2.0, 1e-8));
    REQUIRE_THAT(aabb.GetMax().z, Catch::Matchers::WithinAbs(2.0, 1e-8));
}

TEST_CASE("Inflate")
{
    auto inflate = GENERATE(0.1, -0.1, 1e-6, -1e-6);
    AABB aabb(Vector3<double>(0.5, 0.5, 0.5), Vector3<double>(0.5, 0.5, 0.5));
    aabb.Inflate(inflate);

    REQUIRE_THAT(aabb.GetMin().x, Catch::Matchers::WithinAbs(0.0 - inflate, 1e-8));
    REQUIRE_THAT(aabb.GetMin().y, Catch::Matchers::WithinAbs(0.0 - inflate, 1e-8));
    REQUIRE_THAT(aabb.GetMin().z, Catch::Matchers::WithinAbs(0.0 - inflate, 1e-8));
    REQUIRE_THAT(aabb.GetMax().x, Catch::Matchers::WithinAbs(1.0 + inflate, 1e-8));
    REQUIRE_THAT(aabb.GetMax().y, Catch::Matchers::WithinAbs(1.0 + inflate, 1e-8));
    REQUIRE_THAT(aabb.GetMax().z, Catch::Matchers::WithinAbs(1.0 + inflate, 1e-8));
}
