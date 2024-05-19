#include <catch2/catch_test_macros.hpp>

#include "protocolCraft/Utilities/Templates.hpp"

using namespace ProtocolCraft;

TEST_CASE("Is Type")
{
    // Array
    STATIC_REQUIRE(Internal::IsArray<std::array<int, 5>>);
    STATIC_REQUIRE(Internal::IsArray<std::array<std::map<int, int>, 1>>);
    STATIC_REQUIRE(Internal::IsArray<std::array<std::array<int, 1>, 3>>);
    STATIC_REQUIRE_FALSE(Internal::IsArray<int>);
    STATIC_REQUIRE_FALSE(Internal::IsArray<std::optional<int>>);
    STATIC_REQUIRE_FALSE(Internal::IsArray<std::map<int, int>>);

    // Vector
    STATIC_REQUIRE(Internal::IsVector<std::vector<int>>);
    STATIC_REQUIRE(Internal::IsVector<std::vector<std::map<int, int>>>);
    STATIC_REQUIRE(Internal::IsVector<std::vector<std::vector<int>>>);
    STATIC_REQUIRE_FALSE(Internal::IsVector<int>);
    STATIC_REQUIRE_FALSE(Internal::IsVector<std::optional<int>>);
    STATIC_REQUIRE_FALSE(Internal::IsVector<std::map<int, int>>);

    // Map
    STATIC_REQUIRE(Internal::IsMap<std::map<int, int>>);
    STATIC_REQUIRE(Internal::IsMap<std::map<char, int>>);
    STATIC_REQUIRE(Internal::IsMap<std::map<char, std::map<int, int>>>);
    STATIC_REQUIRE_FALSE(Internal::IsMap<int>);
    STATIC_REQUIRE_FALSE(Internal::IsMap<std::optional<int>>);
    STATIC_REQUIRE_FALSE(Internal::IsMap<std::vector<int>>);

    // Optional
    STATIC_REQUIRE(Internal::IsOptional<std::optional<int>>);
    STATIC_REQUIRE(Internal::IsOptional<std::optional<std::vector<int>>>);
    STATIC_REQUIRE(Internal::IsOptional<std::optional<std::map<char, int>>>);
    STATIC_REQUIRE_FALSE(Internal::IsOptional<int>);
    STATIC_REQUIRE_FALSE(Internal::IsOptional<std::vector<int>>);
    STATIC_REQUIRE_FALSE(Internal::IsOptional<std::map<char, int>>);

    // Pair
    STATIC_REQUIRE(Internal::IsPair<std::pair<int, VarType<int>>>);
    STATIC_REQUIRE(Internal::IsPair<std::pair<int, std::vector<char>>>);
    STATIC_REQUIRE(Internal::IsPair<std::pair<std::pair<int, char>, std::vector<double>>>);
    STATIC_REQUIRE_FALSE(Internal::IsPair<int>);
    STATIC_REQUIRE_FALSE(Internal::IsPair<std::vector<int>>);
    STATIC_REQUIRE_FALSE(Internal::IsPair<std::optional<std::pair<char, int>>>);

    // Bitset
#if PROTOCOL_VERSION > 760 /* > 1.19.2 */
    STATIC_REQUIRE(Internal::IsBitset<std::bitset<5>>);
    STATIC_REQUIRE(Internal::IsBitset<std::bitset<0>>);
    STATIC_REQUIRE(Internal::IsBitset<std::bitset<42>>);
    STATIC_REQUIRE_FALSE(Internal::IsBitset<int>);
    STATIC_REQUIRE_FALSE(Internal::IsBitset<std::vector<int>>);
    STATIC_REQUIRE_FALSE(Internal::IsBitset<std::map<char, int>>);
#endif
}

TEST_CASE("Network Type extraction")
{
    enum class TestEnum
    {
        One,
        Two,
        Three
    };

    struct TestClass
    {

    };

    // Simple type
    STATIC_REQUIRE(std::is_same_v<typename Internal::NetworkType<int>::storage_type, int>);
    STATIC_REQUIRE(std::is_same_v<typename Internal::NetworkType<int>::serialization_type, int>);
    STATIC_REQUIRE(std::is_same_v<typename Internal::NetworkType<TestEnum>::storage_type, TestEnum>);
    STATIC_REQUIRE_FALSE(std::is_same_v<typename Internal::NetworkType<TestEnum>::serialization_type, int>);
    STATIC_REQUIRE_FALSE(std::is_same_v<typename Internal::NetworkType<TestEnum>::serialization_type, std::underlying_type_t<TestEnum>>);
    STATIC_REQUIRE(std::is_same_v<typename Internal::NetworkType<TestClass>::storage_type, TestClass>);
    STATIC_REQUIRE(std::is_same_v<typename Internal::NetworkType<TestClass>::serialization_type, TestClass>);

    // VarType
    STATIC_REQUIRE(std::is_same_v<typename Internal::NetworkType<VarType<int>>::storage_type, int>);
    STATIC_REQUIRE(std::is_same_v<typename Internal::NetworkType<VarType<int>>::serialization_type, VarType<int>>);

    // Array
    STATIC_REQUIRE(std::is_same_v<typename Internal::NetworkType<std::array<int, 4>>::storage_type, std::array<int, 4>>);
    STATIC_REQUIRE(std::is_same_v<typename Internal::NetworkType<std::array<int, 3>>::serialization_type, std::array<int, 3>>);
    STATIC_REQUIRE(std::is_same_v<typename Internal::NetworkType<std::array<VarType<int>, 2>>::storage_type, std::array<int, 2>>);
    STATIC_REQUIRE(std::is_same_v<typename Internal::NetworkType<std::array<VarType<int>, 1>>::serialization_type, std::array<VarType<int>, 1>>);
    STATIC_REQUIRE(std::is_same_v<typename Internal::NetworkType<std::array<std::vector<VarType<int>>, 5>>::storage_type, std::array<std::vector<int>, 5>>);
    STATIC_REQUIRE(std::is_same_v<typename Internal::NetworkType<std::array<std::vector<VarType<int>>, 5>>::serialization_type, std::array<std::vector<VarType<int>>, 5>>);

    // Vector
    STATIC_REQUIRE(std::is_same_v<typename Internal::NetworkType<std::vector<int>>::storage_type, std::vector<int>>);
    STATIC_REQUIRE(std::is_same_v<typename Internal::NetworkType<std::vector<int>>::serialization_type, std::vector<int>>);
    STATIC_REQUIRE(std::is_same_v<typename Internal::NetworkType<std::vector<VarType<int>>>::storage_type, std::vector<int>>);
    STATIC_REQUIRE(std::is_same_v<typename Internal::NetworkType<std::vector<VarType<int>>>::serialization_type, std::vector<VarType<int>>>);
    STATIC_REQUIRE(std::is_same_v<typename Internal::NetworkType<std::vector<std::vector<VarType<int>>>>::storage_type, std::vector<std::vector<int>>>);
    STATIC_REQUIRE(std::is_same_v<typename Internal::NetworkType<std::vector<std::vector<VarType<int>>>>::serialization_type, std::vector<std::vector<VarType<int>>>>);

    // Map
    STATIC_REQUIRE(std::is_same_v<typename Internal::NetworkType<std::map<char, int>>::storage_type, std::map<char, int>>);
    STATIC_REQUIRE(std::is_same_v<typename Internal::NetworkType<std::map<char, int>>::serialization_type, std::map<char, int>>);
    STATIC_REQUIRE(std::is_same_v<typename Internal::NetworkType<std::map<char, VarType<int>>>::storage_type, std::map<char, int>>);
    STATIC_REQUIRE(std::is_same_v<typename Internal::NetworkType<std::map<char, VarType<int>>>::serialization_type, std::map<char, VarType<int>>>);
    STATIC_REQUIRE(std::is_same_v<typename Internal::NetworkType<std::map<char, std::map<int, VarType<int>>>>::storage_type, std::map<char, std::map<int, int>>>);
    STATIC_REQUIRE(std::is_same_v<typename Internal::NetworkType<std::map<char, std::map<int, VarType<int>>>>::serialization_type, std::map<char, std::map<int, VarType<int>>>>);

    // Optional
    STATIC_REQUIRE(std::is_same_v<typename Internal::NetworkType<std::optional<int>>::storage_type, std::optional<int>>);
    STATIC_REQUIRE(std::is_same_v<typename Internal::NetworkType<std::optional<int>>::serialization_type, std::optional<int>>);
    STATIC_REQUIRE(std::is_same_v<typename Internal::NetworkType<std::optional<VarType<int>>>::storage_type, std::optional<int>>);
    STATIC_REQUIRE(std::is_same_v<typename Internal::NetworkType<std::optional<VarType<int>>>::serialization_type, std::optional<VarType<int>>>);

    // Pair
    STATIC_REQUIRE(std::is_same_v<typename Internal::NetworkType<std::pair<int, int>>::storage_type, std::pair<int, int>>);
    STATIC_REQUIRE(std::is_same_v<typename Internal::NetworkType<std::pair<int, int>>::serialization_type, std::pair<int, int>>);
    STATIC_REQUIRE(std::is_same_v<typename Internal::NetworkType<std::pair<int, VarType<int>>>::storage_type, std::pair<int, int>>);
    STATIC_REQUIRE(std::is_same_v<typename Internal::NetworkType<std::pair<int, VarType<int>>>::serialization_type, std::pair<int, VarType<int>>>);
    STATIC_REQUIRE(std::is_same_v<typename Internal::NetworkType<std::pair<std::vector<int>, std::vector<VarType<int>>>>::storage_type, std::pair<std::vector<int>, std::vector<int>>>);
    STATIC_REQUIRE(std::is_same_v<typename Internal::NetworkType<std::pair<std::vector<int>, std::vector<VarType<int>>>>::serialization_type, std::pair<std::vector<int>, std::vector<VarType<int>>>>);

    // Tuple
    STATIC_REQUIRE(std::is_same_v<typename Internal::NetworkType<std::tuple<int, int>>::storage_type, std::tuple<int, int>>);
    STATIC_REQUIRE(std::is_same_v<typename Internal::NetworkType<std::tuple<int, int>>::serialization_type, std::tuple<int, int>>);
    STATIC_REQUIRE(std::is_same_v<typename Internal::NetworkType<std::tuple<int, VarType<int>>>::storage_type, std::tuple<int, int>>);
    STATIC_REQUIRE(std::is_same_v<typename Internal::NetworkType<std::tuple<int, VarType<int>>>::serialization_type, std::tuple<int, VarType<int>>>);
    STATIC_REQUIRE(std::is_same_v<typename Internal::NetworkType<std::tuple<int, DiffType<TestEnum, VarType<int>>>>::storage_type, std::tuple<int, TestEnum>>);
    STATIC_REQUIRE(std::is_same_v<typename Internal::NetworkType<std::tuple<int, DiffType<TestEnum, VarType<int>>>>::serialization_type, std::tuple<int, VarType<int>>>);
    STATIC_REQUIRE(std::is_same_v<typename Internal::NetworkType<std::tuple<int, DiffType<TestEnum, VarType<int>>, TestClass>>::storage_type, std::tuple<int, TestEnum, TestClass>>);
    STATIC_REQUIRE(std::is_same_v<typename Internal::NetworkType<std::tuple<int, DiffType<TestEnum, VarType<int>>, TestClass>>::serialization_type, std::tuple<int, VarType<int>, TestClass>>);

}
