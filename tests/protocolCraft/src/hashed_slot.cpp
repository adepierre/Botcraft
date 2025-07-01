#if PROTOCOL_VERSION > 769 /* > 1.21.4 */
#include <catch2/catch_test_macros.hpp>

#include "protocolCraft/Types/Item/HashedSlot.hpp"
#include "protocolCraft/Types/Components/DataComponentTypeComponent.hpp"
#include "protocolCraft/Types/Components/DataComponentTypeInteger.hpp"
#include "protocolCraft/Types/Components/DataComponentTypeRarity.hpp"

using namespace ProtocolCraft;

TEST_CASE("Hash value", "[!shouldfail]")
{
    Slot slot;
    slot.SetItemId(1);
    slot.SetItemCount(1);
    std::map<Components::DataComponentTypes, std::shared_ptr<Components::DataComponentType>> components;
    std::map<Components::DataComponentTypes, int> expected_hash;

    auto check_result = [&]() {
        slot.SetComponents(Components::DataComponentPatch().SetMap(components));

        HashedSlot hashed_slot(slot);

        REQUIRE(hashed_slot.GetActualItem().has_value());
        REQUIRE(hashed_slot.GetActualItem().value().GetComponents().GetAddedComponents().size() == components.size());
        for (auto& [k, v] : expected_hash)
        {
            REQUIRE_NOTHROW(hashed_slot.GetActualItem().value().GetComponents().GetAddedComponents().at(k));
            CHECK(hashed_slot.GetActualItem().value().GetComponents().GetAddedComponents().at(k) == v);
        }
    };

    SECTION("damage 5")
    {
        std::shared_ptr<Components::DataComponentTypeInteger> damage = std::make_shared<Components::DataComponentTypeInteger>();
        damage->SetValue(5);
        components[Components::DataComponentTypes::Damage] = damage;
        expected_hash[Components::DataComponentTypes::Damage] = 645064431;
        check_result();
    }
    SECTION("damage 5 rare")
    {
        std::shared_ptr<Components::DataComponentTypeInteger> damage = std::make_shared<Components::DataComponentTypeInteger>();
        damage->SetValue(5);
        components[Components::DataComponentTypes::Damage] = damage;
        expected_hash[Components::DataComponentTypes::Damage] = 645064431;

        std::shared_ptr<Components::DataComponentTypeRarity> rarity = std::make_shared<Components::DataComponentTypeRarity>();
        rarity->SetRarityId(2);
        components[Components::DataComponentTypes::Rarity] = rarity;
        expected_hash[Components::DataComponentTypes::Rarity] = -1420566726;
        check_result();
    }
    SECTION("max stack size 10")
    {
        std::shared_ptr<Components::DataComponentTypeInteger> stack_size = std::make_shared<Components::DataComponentTypeInteger>();
        stack_size->SetValue(10);
        components[Components::DataComponentTypes::MaxStackSize] = stack_size;
        expected_hash[Components::DataComponentTypes::MaxStackSize] = -919192125;
        check_result();
    }
    SECTION("item name \"test\"")
    {
        std::shared_ptr<Components::DataComponentTypeComponent> item_name = std::make_shared<Components::DataComponentTypeComponent>();

        // Ugly hack to create a "test" Chat as I don't have constructors for NBT :]
        // TODO: yeah definitely
        const std::string s = "test";
        std::vector<unsigned char> bytes;
        WriteData<char>(8, bytes); // TagString
        WriteData<unsigned short>(static_cast<unsigned short>(s.size()), bytes);
        WriteRawString(s, bytes);
        auto iter = bytes.begin();
        size_t length = bytes.size();
        Chat c;
        c.Read(iter, length);

        item_name->SetComponent(c);
        components[Components::DataComponentTypes::ItemName] = item_name;
        expected_hash[Components::DataComponentTypes::ItemName] = 1541493536;
        check_result();
    }
}
#endif
