#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>

#include <botcraft/Utilities/StringUtilities.hpp>

#include <tuple>

#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
TEST_CASE("ISO 8601 fractional seconds are converted to milliseconds", "[string_utilities]")
{
    const auto [timestamp, expected] = GENERATE(Catch::Generators::table<const char*, long long int>({
        { "2026-10-14T12:34:56Z",           1791981296000LL },
        { "2026-10-14T12:34:56.1Z",         1791981296100LL },
        { "2026-10-14T12:34:56.12Z",        1791981296120LL },
        { "2026-10-14T12:34:56.123Z",       1791981296123LL },
        { "2026-10-14T12:34:56.1234Z",      1791981296123LL },
        { "2026-10-14T12:34:56.12345Z",     1791981296123LL },
        { "2026-10-14T12:34:56.123456Z",    1791981296123LL },
        { "2026-10-14T12:34:56.1234567Z",   1791981296123LL },
        { "2026-10-14T12:34:56.12345678Z",  1791981296123LL },
        { "2026-10-14T12:34:56.123456789Z", 1791981296123LL },
        { "2026-10-14T12:34:56.000001Z",    1791981296000LL },
        { "2026-10-14T12:34:56.000999Z",    1791981296000LL },
        { "2026-10-14T12:34:56.001Z",       1791981296001LL },
        { "2026-10-14T12:34:56.999999999Z", 1791981296999LL },
    }));

    CAPTURE(timestamp);
    REQUIRE(Botcraft::Utilities::TimestampMilliFromISO8601(timestamp) == expected);
}

TEST_CASE("ISO 8601 UTC dates are converted without 32-bit seconds overflow", "[string_utilities]")
{
    const auto [timestamp, expected] = GENERATE(Catch::Generators::table<const char*, long long int>({
        { "1970-01-01T00:00:00Z",         0LL },
        { "1969-12-31T23:59:59.999Z",    -1LL },
        { "2024-02-29T00:00:00.000000Z", 1709164800000LL },
        { "2038-01-19T03:14:08.000000Z", 2147483648000LL },
        { "2040-01-01T00:00:00.123456Z", 2208988800123LL },
    }));

    CAPTURE(timestamp);
    REQUIRE(Botcraft::Utilities::TimestampMilliFromISO8601(timestamp) == expected);
}

TEST_CASE("Malformed ISO 8601 UTC fractions and suffixes fail without throwing", "[string_utilities]")
{
    const auto timestamp = GENERATE(
        "",
        "not-a-timestamp",
        "2026-10-14T12:34:56.Z",
        "2026-10-14T12:34:56.fooZ",
        "2026-10-14T12:34:56.12fooZ",
        "2026-10-14T12:34:56.123Ztrailing"
    );

    CAPTURE(timestamp);
    REQUIRE(Botcraft::Utilities::TimestampMilliFromISO8601(timestamp) == 0);
}
#endif
