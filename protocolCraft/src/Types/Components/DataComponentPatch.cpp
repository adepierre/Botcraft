#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#include "protocolCraft/Types/Components/DataComponentPatch.hpp"
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
                if (type <= DataComponentTypes::None || type >= DataComponentTypes::NUM_DATA_COMPONENT_TYPES)
                {
                    throw std::runtime_error("Unable to create data component with id: " + std::to_string(static_cast<int>(type)) + ".");
                }

                std::shared_ptr<DataComponentType> data = nullptr;

                switch (type)
                {
                case DataComponentTypes::CanPlaceOn:
                case DataComponentTypes::CanBreak:
                    data = std::make_shared<DataComponentTypeAdventureModePredicate>();
                    break;
                case DataComponentTypes::Trim:
                    data = std::make_shared<DataComponentTypeArmorTrim>();
                    break;
                case DataComponentTypes::BannerPatterns:
                    data = std::make_shared<DataComponentTypeBannerPatternLayers>();
                    break;
                case DataComponentTypes::BlockState:
                    data = std::make_shared<DataComponentTypeBlockItemStateProperties>();
                    break;
                case DataComponentTypes::EnchantmentGlintOverride:
                    data = std::make_shared<DataComponentTypeBoolean>();
                    break;
                case DataComponentTypes::BundleContents:
                    data = std::make_shared<DataComponentTypeBundleContents>();
                    break;
                case DataComponentTypes::ChargedProjectiles:
                    data = std::make_shared<DataComponentTypeChargedProjectiles>();
                    break;
                case DataComponentTypes::CustomName:
                case DataComponentTypes::ItemName:
                    data = std::make_shared<DataComponentTypeComponent>();
                    break;
                case DataComponentTypes::BlockEntityData:
                case DataComponentTypes::BucketEntityData:
                case DataComponentTypes::EntityData:
                    data = std::make_shared<DataComponentTypeCustomData>();
                    break;
                case DataComponentTypes::CustomModelData:
                    data = std::make_shared<DataComponentTypeCustomModelData>();
                    break;
                case DataComponentTypes::CustomData:
                case DataComponentTypes::IntangibleProjectile:
                case DataComponentTypes::MapDecorations:
                case DataComponentTypes::DebugStickState:
                case DataComponentTypes::Recipes:
                case DataComponentTypes::Lock:
                case DataComponentTypes::ContainerLoot:
                    // Component with no nework serializer specified fallback to NBT
                    data = std::make_shared<DataComponentTypeDefault>();
                    break;
                case DataComponentTypes::BaseColor:
                    data = std::make_shared<DataComponentTypeDyeColor>();
                    break;
                case DataComponentTypes::DyedColor:
                    data = std::make_shared<DataComponentTypeDyedItemColor>();
                    break;
                case DataComponentTypes::FireworkExplosion:
                    data = std::make_shared<DataComponentTypeFireworkExplosion>();
                    break;
                case DataComponentTypes::Fireworks:
                    data = std::make_shared<DataComponentTypeFireworks>();
                    break;
                case DataComponentTypes::Food:
                    data = std::make_shared<DataComponentTypeFoodProperties>();
                    break;
                case DataComponentTypes::Instrument:
                    data = std::make_shared<DataComponentTypeHolderInstrument>();
                    break;
                case DataComponentTypes::MaxStackSize:
                case DataComponentTypes::MaxDamage:
                case DataComponentTypes::Damage:
                case DataComponentTypes::RepairCost:
                case DataComponentTypes::OminousBottleAmplifier:
                    data = std::make_shared<DataComponentTypeInteger>();
                    break;
                case DataComponentTypes::AttributeModifiers:
                    data = std::make_shared<DataComponentTypeItemAttributeModifiers>();
                    break;
                case DataComponentTypes::Container:
                    data = std::make_shared<DataComponentTypeItemContainerContents>();
                    break;
                case DataComponentTypes::Enchantments:
                case DataComponentTypes::StoredEnchantments:
                    data = std::make_shared<DataComponentTypeItemEnchantments>();
                    break;
                case DataComponentTypes::Lore:
                    data = std::make_shared<DataComponentTypeItemLore>();
                    break;
                case DataComponentTypes::Bees:
                    data = std::make_shared<DataComponentTypeListBeehiveBlockEntityOccupant>();
                    break;
                case DataComponentTypes::LodestoneTracker:
                    data = std::make_shared<DataComponentTypeLodestoneTracker>();
                    break;
                case DataComponentTypes::MapId:
                    data = std::make_shared<DataComponentTypeMapId>();
                    break;
                case DataComponentTypes::MapColor:
                    data = std::make_shared<DataComponentTypeMapItemColor>();
                    break;
                case DataComponentTypes::MapPostProcessing:
                    data = std::make_shared<DataComponentTypeMapPostProcessing>();
                    break;
                case DataComponentTypes::PotDecorations:
                    data = std::make_shared<DataComponentTypePotDecorations>();
                    break;
                case DataComponentTypes::PotionContents:
                    data = std::make_shared<DataComponentTypePotionContents>();
                    break;
                case DataComponentTypes::Rarity:
                    data = std::make_shared<DataComponentTypeRarity>();
                    break;
                case DataComponentTypes::Profile:
                    data = std::make_shared<DataComponentTypeResolvableProfile>();
                    break;
                case DataComponentTypes::NoteBlockSound:
                    data = std::make_shared<DataComponentTypeResourceLocation>();
                    break;
                case DataComponentTypes::SuspiciousStewEffects:
                    data = std::make_shared<DataComponentTypeSuspiciousStewEffects>();
                    break;
                case DataComponentTypes::Tool:
                    data = std::make_shared<DataComponentTypeTool>();
                    break;
                case DataComponentTypes::Unbreakable:
                    data = std::make_shared<DataComponentTypeUnbreakable>();
                    break;
                case DataComponentTypes::HideAdditionalTooltip:
                case DataComponentTypes::HideTooltip:
                case DataComponentTypes::CreativeSlotLock:
                case DataComponentTypes::FireResistant:
                    data = std::make_shared<DataComponentTypeUnit>();
                    break;
                case DataComponentTypes::WritableBookContent:
                    data = std::make_shared<DataComponentTypeWritableBookContent>();
                    break;
                case DataComponentTypes::WrittenBookContent:
                    data = std::make_shared<DataComponentTypeWrittenBookContent>();
                    break;
                default:
                    // Should never happen but will make the compilers happy
                    throw std::runtime_error("Unable to create data component with id: " + std::to_string(static_cast<int>(type)) + ".");
                    break;
                }

                if (data != nullptr)
                {
                    data->Read(iter, length);
                }
                map.insert({ type, data });
            }

            for (int i = 0; i < num_void; ++i)
            for (int i = 0; i < num_data; ++i)
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
