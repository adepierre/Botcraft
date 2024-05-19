#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#include "protocolCraft/Types/Components/DataComponents.hpp"
#include "protocolCraft/Types/Components/DataComponentType.hpp"

#include "protocolCraft/Types/Components/DataComponentTypeAdventureModePredicate.hpp"
#include "protocolCraft/Types/Components/DataComponentTypeArmorTrim.hpp"
#include "protocolCraft/Types/Components/DataComponentTypeBannerPatternLayers.hpp"
#include "protocolCraft/Types/Components/DataComponentTypeBlockItemStateProperties.hpp"
#include "protocolCraft/Types/Components/DataComponentTypeBoolean.hpp"
#include "protocolCraft/Types/Components/DataComponentTypeBundleContents.hpp"
#include "protocolCraft/Types/Components/DataComponentTypeChargedProjectiles.hpp"
#include "protocolCraft/Types/Components/DataComponentTypeComponent.hpp"
#include "protocolCraft/Types/Components/DataComponentTypeCustomModelData.hpp"
#include "protocolCraft/Types/Components/DataComponentTypeDefault.hpp"
#include "protocolCraft/Types/Components/DataComponentTypeDyeColor.hpp"
#include "protocolCraft/Types/Components/DataComponentTypeDyedItemColor.hpp"
#include "protocolCraft/Types/Components/DataComponentTypeFireworkExplosion.hpp"
#include "protocolCraft/Types/Components/DataComponentTypeFireworks.hpp"
#include "protocolCraft/Types/Components/DataComponentTypeFoodProperties.hpp"
#include "protocolCraft/Types/Components/DataComponentTypeHolderInstrument.hpp"
#include "protocolCraft/Types/Components/DataComponentTypeInteger.hpp"
#include "protocolCraft/Types/Components/DataComponentTypeItemAttributeModifiers.hpp"
#include "protocolCraft/Types/Components/DataComponentTypeItemContainerContents.hpp"
#include "protocolCraft/Types/Components/DataComponentTypeItemEnchantments.hpp"
#include "protocolCraft/Types/Components/DataComponentTypeItemLore.hpp"
#include "protocolCraft/Types/Components/DataComponentTypeListBeehiveBlockEntityOccupant.hpp"
#include "protocolCraft/Types/Components/DataComponentTypeLodestoneTracker.hpp"
#include "protocolCraft/Types/Components/DataComponentTypeMapId.hpp"
#include "protocolCraft/Types/Components/DataComponentTypeMapItemColor.hpp"
#include "protocolCraft/Types/Components/DataComponentTypeMapPostProcessing.hpp"
#include "protocolCraft/Types/Components/DataComponentTypePotDecorations.hpp"
#include "protocolCraft/Types/Components/DataComponentTypePotionContents.hpp"
#include "protocolCraft/Types/Components/DataComponentTypeRarity.hpp"
#include "protocolCraft/Types/Components/DataComponentTypeResolvableProfile.hpp"
#include "protocolCraft/Types/Components/DataComponentTypeResourceLocation.hpp"
#include "protocolCraft/Types/Components/DataComponentTypeSuspiciousStewEffects.hpp"
#include "protocolCraft/Types/Components/DataComponentTypeTool.hpp"
#include "protocolCraft/Types/Components/DataComponentTypeUnbreakable.hpp"
#include "protocolCraft/Types/Components/DataComponentTypeUnit.hpp"
#include "protocolCraft/Types/Components/DataComponentTypeWritableBookContent.hpp"
#include "protocolCraft/Types/Components/DataComponentTypeWrittenBookContent.hpp"

namespace ProtocolCraft
{
    namespace Components
    {
        std::string_view DataComponentTypesToString(const DataComponentTypes type)
        {
            static constexpr std::array<std::string_view, static_cast<size_t>(DataComponentTypes::NUM_DATA_COMPONENT_TYPES)> names = {
                "custom_data",
                "max_stack_size",
                "max_damage",
                "damage",
                "unbreakable",
                "custom_name",
                "item_name",
                "lore",
                "rarity",
                "enchantments",
                "can_place_on",
                "can_break",
                "attribute_modifiers",
                "custom_model_data",
                "hide_additional_tooltip",
                "hide_tooltip",
                "repair_cost",
                "creative_slot_lock",
                "enchantment_glint_override",
                "intangible_projectile",
                "food",
                "fire_resistant",
                "tool",
                "stored_enchantments",
                "dyed_color",
                "map_color",
                "map_id",
                "map_decorations",
                "map_post_processing",
                "charged_projectiles",
                "bundle_contents",
                "potion_contents",
                "suspicious_stew_effects",
                "writable_book_content",
                "written_book_content",
                "trim",
                "debug_stick_state",
                "entity_data",
                "bucket_entity_data",
                "block_entity_data",
                "instrument",
                "ominous_bottle_amplifier",
                "recipes",
                "lodestone_tracker",
                "firework_explosion",
                "fireworks",
                "profile",
                "note_block_sound",
                "banner_patterns",
                "base_color",
                "pot_decorations",
                "container",
                "block_state",
                "bees",
                "lock",
                "container_loot",
            };
            if (type <= DataComponentTypes::None || type >= DataComponentTypes::NUM_DATA_COMPONENT_TYPES)
            {
                return "";
            }
            return names[static_cast<size_t>(type)];
        }

        std::shared_ptr<DataComponentType> CreateComponentType(const DataComponentTypes type)
        {
            if (type <= DataComponentTypes::None || type >= DataComponentTypes::NUM_DATA_COMPONENT_TYPES)
            {
                throw std::runtime_error("Unable to create data component with id: " + std::to_string(static_cast<int>(type)) + ".");
            }

            switch (type)
            {
            case DataComponentTypes::CanPlaceOn:
            case DataComponentTypes::CanBreak:
                return std::make_shared<DataComponentTypeAdventureModePredicate>();
            case DataComponentTypes::Trim:
                return std::make_shared<DataComponentTypeArmorTrim>();
            case DataComponentTypes::BannerPatterns:
                return std::make_shared<DataComponentTypeBannerPatternLayers>();
            case DataComponentTypes::BlockState:
                return std::make_shared<DataComponentTypeBlockItemStateProperties>();
            case DataComponentTypes::EnchantmentGlintOverride:
                return std::make_shared<DataComponentTypeBoolean>();
            case DataComponentTypes::BundleContents:
                return std::make_shared<DataComponentTypeBundleContents>();
            case DataComponentTypes::ChargedProjectiles:
                return std::make_shared<DataComponentTypeChargedProjectiles>();
            case DataComponentTypes::CustomName:
            case DataComponentTypes::ItemName:
                return std::make_shared<DataComponentTypeComponent>();
            case DataComponentTypes::BlockEntityData:
            case DataComponentTypes::BucketEntityData:
            case DataComponentTypes::EntityData:
                return std::make_shared<DataComponentTypeCustomData>();
            case DataComponentTypes::CustomModelData:
                return std::make_shared<DataComponentTypeCustomModelData>();
            case DataComponentTypes::CustomData:
            case DataComponentTypes::IntangibleProjectile:
            case DataComponentTypes::MapDecorations:
            case DataComponentTypes::DebugStickState:
            case DataComponentTypes::Recipes:
            case DataComponentTypes::Lock:
            case DataComponentTypes::ContainerLoot:
                // Component with no nework serializer specified fallback to NBT
                return std::make_shared<DataComponentTypeDefault>();
            case DataComponentTypes::BaseColor:
                return std::make_shared<DataComponentTypeDyeColor>();
            case DataComponentTypes::DyedColor:
                return std::make_shared<DataComponentTypeDyedItemColor>();
            case DataComponentTypes::FireworkExplosion:
                return std::make_shared<DataComponentTypeFireworkExplosion>();
            case DataComponentTypes::Fireworks:
                return std::make_shared<DataComponentTypeFireworks>();
            case DataComponentTypes::Food:
                return std::make_shared<DataComponentTypeFoodProperties>();
            case DataComponentTypes::Instrument:
                return std::make_shared<DataComponentTypeHolderInstrument>();
            case DataComponentTypes::MaxStackSize:
            case DataComponentTypes::MaxDamage:
            case DataComponentTypes::Damage:
            case DataComponentTypes::RepairCost:
            case DataComponentTypes::OminousBottleAmplifier:
                return std::make_shared<DataComponentTypeInteger>();
            case DataComponentTypes::AttributeModifiers:
                return std::make_shared<DataComponentTypeItemAttributeModifiers>();
            case DataComponentTypes::Container:
                return std::make_shared<DataComponentTypeItemContainerContents>();
            case DataComponentTypes::Enchantments:
            case DataComponentTypes::StoredEnchantments:
                return std::make_shared<DataComponentTypeItemEnchantments>();
            case DataComponentTypes::Lore:
                return std::make_shared<DataComponentTypeItemLore>();
            case DataComponentTypes::Bees:
                return std::make_shared<DataComponentTypeListBeehiveBlockEntityOccupant>();
            case DataComponentTypes::LodestoneTracker:
                return std::make_shared<DataComponentTypeLodestoneTracker>();
            case DataComponentTypes::MapId:
                return std::make_shared<DataComponentTypeMapId>();
            case DataComponentTypes::MapColor:
                return std::make_shared<DataComponentTypeMapItemColor>();
            case DataComponentTypes::MapPostProcessing:
                return std::make_shared<DataComponentTypeMapPostProcessing>();
            case DataComponentTypes::PotDecorations:
                return std::make_shared<DataComponentTypePotDecorations>();
            case DataComponentTypes::PotionContents:
                return std::make_shared<DataComponentTypePotionContents>();
            case DataComponentTypes::Rarity:
                return std::make_shared<DataComponentTypeRarity>();
            case DataComponentTypes::Profile:
                return std::make_shared<DataComponentTypeResolvableProfile>();
            case DataComponentTypes::NoteBlockSound:
                return std::make_shared<DataComponentTypeResourceLocation>();
            case DataComponentTypes::SuspiciousStewEffects:
                return std::make_shared<DataComponentTypeSuspiciousStewEffects>();
            case DataComponentTypes::Tool:
                return std::make_shared<DataComponentTypeTool>();
            case DataComponentTypes::Unbreakable:
                return std::make_shared<DataComponentTypeUnbreakable>();
            case DataComponentTypes::HideAdditionalTooltip:
            case DataComponentTypes::HideTooltip:
            case DataComponentTypes::CreativeSlotLock:
            case DataComponentTypes::FireResistant:
                return std::make_shared<DataComponentTypeUnit>();
            case DataComponentTypes::WritableBookContent:
                return std::make_shared<DataComponentTypeWritableBookContent>();
            case DataComponentTypes::WrittenBookContent:
                return std::make_shared<DataComponentTypeWrittenBookContent>();
            default:
                // Should never happen but will make the compilers happy
                throw std::runtime_error("Unable to create data component with id: " + std::to_string(static_cast<int>(type)) + ".");
            }
        }

        DataComponentPredicate::~DataComponentPredicate()
        {

        }

        const std::map<DataComponentTypes, std::shared_ptr<DataComponentType>>& DataComponentPredicate::GetMap() const
        {
            return map;
        }

        void DataComponentPredicate::SetMap(const std::map<DataComponentTypes, std::shared_ptr<DataComponentType>>& map_)
        {
            map = map_;
        }

        void DataComponentPredicate::ReadImpl(ReadIterator& iter, size_t& length)
        {
            // special case, dynamic factory
            map = ReadMap<DataComponentTypes, std::shared_ptr<DataComponentType>>(iter, length,
                [](ReadIterator& i, size_t& l)
                {
                    const DataComponentTypes first = static_cast<DataComponentTypes>(static_cast<int>(ReadData<VarInt>(i, l)));
                    std::shared_ptr<DataComponentType> second = CreateComponentType(first);
                    if (second != nullptr)
                    {
                        second->Read(i, l);
                    }

                    return std::make_pair(first, second);
                });
        }

        void DataComponentPredicate::WriteImpl(WriteContainer& container) const
        {
            // special case, dynamic factory
            WriteMap<DataComponentTypes, std::shared_ptr<DataComponentType>>(map, container,
                [](const std::pair<const DataComponentTypes, std::shared_ptr<DataComponentType>>& p, WriteContainer& c)
                {
                    WriteData<VarInt>(static_cast<int>(p.first), c);
                    if (p.second != nullptr)
                    {
                        p.second->Write(c);
                    }
                });
        }

        Json::Value DataComponentPredicate::SerializeImpl() const
        {
            Json::Value output;

            output["map"] = Json::Array();
            for (const auto& p : map)
            {
                output["map"].push_back({
                    { "name", DataComponentTypesToString(p.first) },
                    { "data", p.second == nullptr ? nullptr : p.second->Serialize() }
                });
            }

            return output;
        }


        DataComponentPatch::~DataComponentPatch()
        {

        }

        const std::map<DataComponentTypes, std::shared_ptr<DataComponentType>>& DataComponentPatch::GetMap() const
        {
            return map;
        }

        void DataComponentPatch::SetMap(const std::map<DataComponentTypes, std::shared_ptr<DataComponentType>>& map_)
        {
            map = map_;
        }

        void DataComponentPatch::ReadImpl(ReadIterator& iter, size_t& length)
        {
            const int num_data = ReadData<VarInt>(iter, length);
            const int num_void = ReadData<VarInt>(iter, length);

            map.clear();

            for (int i = 0; i < num_data; ++i)
            {
                const DataComponentTypes type = static_cast<DataComponentTypes>(static_cast<int>(ReadData<VarInt>(iter, length)));
                std::shared_ptr<DataComponentType> data = CreateComponentType(type);

                if (data != nullptr)
                {
                    data->Read(iter, length);
                }
                map.insert({ type, data });
            }

            for (int i = 0; i < num_void; ++i)
            {
                const DataComponentTypes type = static_cast<DataComponentTypes>(static_cast<int>(ReadData<VarInt>(iter, length)));
                map.insert({ type, nullptr });
            }
        }

        void DataComponentPatch::WriteImpl(WriteContainer& container) const
        {
            int num_data = 0;
            for (const auto& p : map)
            {
                num_data += p.second != nullptr;
            }
            const int num_void = static_cast<int>(map.size()) - num_data;

            WriteData<VarInt>(num_data, container);
            WriteData<VarInt>(num_void, container);

            for (const auto& p : map)
            {
                if (p.second == nullptr)
                {
                    continue;
                }
                WriteData<VarInt>(static_cast<int>(p.first), container);
                p.second->Write(container);
            }

            for (const auto& p : map)
            {
                if (p.second != nullptr)
                {
                    continue;
                }
                WriteData<VarInt>(static_cast<int>(p.first), container);
            }
        }

        Json::Value DataComponentPatch::SerializeImpl() const
        {
            Json::Value output;

            output["map"] = Json::Array();
            for (const auto& p : map)
            {
                output["map"].push_back({
                    { "name", DataComponentTypesToString(p.first) },
                    { "data", p.second == nullptr ? nullptr : p.second->Serialize() }
                    });
            }

            return output;
        }
    }
}
#endif
