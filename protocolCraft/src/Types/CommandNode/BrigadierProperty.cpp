#if PROTOCOL_VERSION > 344
#include "protocolCraft/Types/CommandNode/BrigadierProperty.hpp"

#include "protocolCraft/Types/CommandNode/BrigadierPropertyDouble.hpp"
#include "protocolCraft/Types/CommandNode/BrigadierPropertyFloat.hpp"
#include "protocolCraft/Types/CommandNode/BrigadierPropertyInteger.hpp"
#include "protocolCraft/Types/CommandNode/BrigadierPropertyLong.hpp"
#include "protocolCraft/Types/CommandNode/BrigadierPropertyString.hpp"
#include "protocolCraft/Types/CommandNode/BrigadierPropertyEntity.hpp"
#include "protocolCraft/Types/CommandNode/BrigadierPropertyScoreHolder.hpp"
#include "protocolCraft/Types/CommandNode/BrigadierPropertyResourceOrTag.hpp"
#if PROTOCOL_VERSION > 761
#include "protocolCraft/Types/CommandNode/BrigadierPropertyTime.hpp"
#endif
#if PROTOCOL_VERSION < 759
#include "protocolCraft/Types/CommandNode/BrigadierPropertyRange.hpp"
#endif
#include "protocolCraft/Types/CommandNode/BrigadierPropertyNone.hpp"

#include <stdexcept>

namespace ProtocolCraft
{
    BrigadierProperty::~BrigadierProperty()
    {

    }

#if PROTOCOL_VERSION < 759
    std::shared_ptr<BrigadierProperty> BrigadierProperty::CreateProperties(const Identifier& parser_identifier)
    {
        if (parser_identifier.GetFull() == "brigadier:double")
        {
            return std::make_shared<BrigadierPropertyDouble>();
        }
        else if (parser_identifier.GetFull() == "brigadier:float")
        {
            return std::make_shared<BrigadierPropertyFloat>();
        }
        else if (parser_identifier.GetFull() == "brigadier:integer")
        {
            return std::make_shared<BrigadierPropertyInteger>();
        }
        else if (parser_identifier.GetFull() == "brigadier:long")
        {
            return std::make_shared<BrigadierPropertyLong>();
        }
        else if (parser_identifier.GetFull() == "brigadier:string")
        {
            return std::make_shared<BrigadierPropertyString>();
        }
        else if (parser_identifier.GetFull() == "minecraft:entity")
        {
            return std::make_shared<BrigadierPropertyEntity>();
        }
        else if (parser_identifier.GetFull() == "minecraft:resource_or_tag")
        {
            return std::make_shared<BrigadierPropertyResourceOrTag>();
        }
        else if (parser_identifier.GetFull() == "minecraft:resource")
        {
            return std::make_shared<BrigadierPropertyResourceOrTag>();
        }
        else if (parser_identifier.GetFull() == "minecraft:score_holder")
        {
            return std::make_shared<BrigadierPropertyScoreHolder>();
        }
        else if (parser_identifier.GetFull() == "minecraft:range")
        {
            return std::make_shared<BrigadierPropertyRange>();
        }
        else if (parser_identifier.GetFull() == "forge:modid" ||
                 parser_identifier.GetFull() == "forge:enum")
        {
            throw std::runtime_error("Unable to create command node parser with id: " + parser_identifier.GetFull() + ". Modded protocol is not supported.");
        }
        else
        {
            return std::make_shared<BrigadierPropertyNone>();
        }
    }
#else
    std::shared_ptr<BrigadierProperty> BrigadierProperty::CreateProperties(const BrigadierPropertyType parser_id)
    {
        switch (parser_id)
        {
        case BrigadierPropertyType::Float:
            return std::make_shared<BrigadierPropertyFloat>();
        case BrigadierPropertyType::Double:
            return std::make_shared<BrigadierPropertyDouble>();
        case BrigadierPropertyType::Integer:
            return std::make_shared<BrigadierPropertyInteger>();
        case BrigadierPropertyType::Long:
            return std::make_shared<BrigadierPropertyLong>();
        case BrigadierPropertyType::String:
            return std::make_shared<BrigadierPropertyString>();
        case BrigadierPropertyType::Entity:
            return std::make_shared<BrigadierPropertyEntity>();
        case BrigadierPropertyType::ScoreHolder:
            return std::make_shared<BrigadierPropertyScoreHolder>();
#if PROTOCOL_VERSION > 761
        case BrigadierPropertyType::Time:
            return std::make_shared<BrigadierPropertyTime>();
#endif
        case BrigadierPropertyType::ResourceOrTag:
        case BrigadierPropertyType::Resource:
#if PROTOCOL_VERSION > 760
        case BrigadierPropertyType::ResourceOrTagKey:
        case BrigadierPropertyType::ResourceKey:
#endif
            return std::make_shared<BrigadierPropertyResourceOrTag>();
        case BrigadierPropertyType::Bool:
        case BrigadierPropertyType::GameProfile:
        case BrigadierPropertyType::BlockPos:
        case BrigadierPropertyType::ColumnPos:
        case BrigadierPropertyType::Vec3:
        case BrigadierPropertyType::Vec2:
        case BrigadierPropertyType::BlockState:
        case BrigadierPropertyType::BlockPredicate:
        case BrigadierPropertyType::ItemStack:
        case BrigadierPropertyType::ItemPredicate:
        case BrigadierPropertyType::Color:
        case BrigadierPropertyType::Component:
        case BrigadierPropertyType::Message:
        case BrigadierPropertyType::NbtCompoundTag:
        case BrigadierPropertyType::NbtTag:
        case BrigadierPropertyType::NbtPath:
        case BrigadierPropertyType::Objective:
        case BrigadierPropertyType::ObjectiveCriteria:
        case BrigadierPropertyType::Operation:
        case BrigadierPropertyType::Particle:
        case BrigadierPropertyType::Angle:
        case BrigadierPropertyType::Rotation:
        case BrigadierPropertyType::ScoreboardSlot:
        case BrigadierPropertyType::Swizzle:
        case BrigadierPropertyType::Team:
        case BrigadierPropertyType::ItemSlot:
        case BrigadierPropertyType::ResourceLocation:
#if PROTOCOL_VERSION < 761
        case BrigadierPropertyType::MobEffect:
#endif
        case BrigadierPropertyType::Function:
        case BrigadierPropertyType::EntityAnchor:
#if PROTOCOL_VERSION < 761
        case BrigadierPropertyType::ItemEnchantment:
        case BrigadierPropertyType::EntitySummon:
#endif
        case BrigadierPropertyType::IntRange:
        case BrigadierPropertyType::FloatRange:
        case BrigadierPropertyType::Dimension:
#if PROTOCOL_VERSION > 760
        case BrigadierPropertyType::Gamemode:
#endif
#if PROTOCOL_VERSION < 762
        case BrigadierPropertyType::Time:
#endif
        case BrigadierPropertyType::TemplateMirror:
        case BrigadierPropertyType::TemplateRotation:
#if PROTOCOL_VERSION > 761
        case BrigadierPropertyType::Heightmap:
#endif
        case BrigadierPropertyType::Uuid:
            return std::make_shared<BrigadierPropertyNone>();
        default:
            throw std::runtime_error("Unable to create command node parser with id: " + std::to_string(static_cast<int>(parser_id)) + ". Are you using a mod? Modded protocol is not supported.");
        }
    }
#endif
}
#endif
