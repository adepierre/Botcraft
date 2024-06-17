#if PROTOCOL_VERSION > 344 /* > 1.12.2 */
#include "protocolCraft/Types/CommandNode/BrigadierProperty.hpp"
#include "protocolCraft/Utilities/AutoSerializedToJson.hpp"

#include "protocolCraft/Types/CommandNode/BrigadierPropertyDouble.hpp"
#include "protocolCraft/Types/CommandNode/BrigadierPropertyFloat.hpp"
#include "protocolCraft/Types/CommandNode/BrigadierPropertyInteger.hpp"
#include "protocolCraft/Types/CommandNode/BrigadierPropertyLong.hpp"
#include "protocolCraft/Types/CommandNode/BrigadierPropertyString.hpp"
#include "protocolCraft/Types/CommandNode/BrigadierPropertyEntity.hpp"
#include "protocolCraft/Types/CommandNode/BrigadierPropertyScoreHolder.hpp"
#include "protocolCraft/Types/CommandNode/BrigadierPropertyResourceOrTag.hpp"
#if PROTOCOL_VERSION > 761 /* > 1.19.3 */
#include "protocolCraft/Types/CommandNode/BrigadierPropertyTime.hpp"
#endif
#if PROTOCOL_VERSION < 759 /* < 1.19 */
#include "protocolCraft/Types/CommandNode/BrigadierPropertyRange.hpp"
#endif
#include "protocolCraft/Types/CommandNode/BrigadierPropertyNone.hpp"

#include <stdexcept>

namespace ProtocolCraft
{
    DEFINE_SERIALIZE(BrigadierPropertyDouble);
    DEFINE_NETWORK_TYPE(BrigadierPropertyEntity);
    DEFINE_SERIALIZE(BrigadierPropertyFloat);
    DEFINE_SERIALIZE(BrigadierPropertyInteger);
    DEFINE_SERIALIZE(BrigadierPropertyLong);
    DEFINE_NETWORK_TYPE(BrigadierPropertyNone);
#if PROTOCOL_VERSION < 759 /* < 1.19 */
    DEFINE_NETWORK_TYPE(BrigadierPropertyRange);
#endif
    DEFINE_NETWORK_TYPE(BrigadierPropertyResourceOrTag);
    DEFINE_NETWORK_TYPE(BrigadierPropertyScoreHolder);
    DEFINE_NETWORK_TYPE(BrigadierPropertyString);
#if PROTOCOL_VERSION > 761 /* > 1.19.3 */
    DEFINE_NETWORK_TYPE(BrigadierPropertyTime);
#endif

    BrigadierProperty::~BrigadierProperty()
    {

    }

#if PROTOCOL_VERSION < 759 /* < 1.19 */
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
        if (parser_id <= BrigadierPropertyType::None || parser_id >= BrigadierPropertyType::NUM_BRIGADIER_PROPERTY_TYPE)
        {
            throw std::runtime_error("Unable to create command node parser with id: " + std::to_string(static_cast<int>(parser_id)) + ". Are you using a mod? Modded protocol is not supported.");
        }
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
#if PROTOCOL_VERSION > 761 /* > 1.19.3 */
        case BrigadierPropertyType::Time:
            return std::make_shared<BrigadierPropertyTime>();
#endif
        case BrigadierPropertyType::ResourceOrTag:
        case BrigadierPropertyType::Resource:
#if PROTOCOL_VERSION > 760 /* > 1.19.2 */
        case BrigadierPropertyType::ResourceOrTagKey:
        case BrigadierPropertyType::ResourceKey:
#endif
            return std::make_shared<BrigadierPropertyResourceOrTag>();
        default:
            return std::make_shared<BrigadierPropertyNone>();
        }
    }
#endif
}
#endif
