#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include <catch2/generators/catch_generators.hpp>

#include <botcraft/Game/Physics/AABB.hpp>

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

TEST_CASE("GetClosestPoint")
{
    // AABB going from (1.0, 2.0, 3.0) to (5.0, 6.0, 7.0)
    const AABB aabb(Vector3<double>(3.0, 4.0, 5.0), Vector3<double>(2.0, 2.0, 2.0));

    Vector3<double> point;
    Vector3<double> closest_point;

    SECTION("Inside")
    {
        point = Vector3<double>(2.0, 3.0, 4.0);
        closest_point = Vector3<double>(2.0, 3.0, 4.0);
    }

    SECTION("Close to an edge")
    {
        point = Vector3<double>(6.0, 4.0, 5.0);
        closest_point = Vector3<double>(5.0, 4.0, 5.0);
    }

    SECTION("Close to a corner")
    {
        point = Vector3<double>(0.0, 1.0, 2.0);
        closest_point = Vector3<double>(1.0, 2.0, 3.0);
    }

    SECTION("Close to a face")
    {
        point = Vector3<double>(3.0, 8.0, 5.0);
        closest_point = Vector3<double>(3.0, 6.0, 5.0);
    }

    const Vector3<double> calculated_closest = aabb.GetClosestPoint(point);
    REQUIRE(calculated_closest.x == closest_point.x);
    REQUIRE(calculated_closest.y == closest_point.y);
    REQUIRE(calculated_closest.z == closest_point.z);
}
