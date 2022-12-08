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
#include "protocolCraft/Types/CommandNode/BrigadierPropertyRange.hpp"
#include "protocolCraft/Types/CommandNode/BrigadierPropertyNone.hpp"

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
        else
        {
            return std::make_shared<BrigadierPropertyNone>();
        }
    }
#else
    std::shared_ptr<BrigadierProperty> BrigadierProperty::CreateProperties(const int parser_id)
    {
        switch (parser_id)
        {
        case 1:
            return std::make_shared<BrigadierPropertyFloat>();
        case 2:
            return std::make_shared<BrigadierPropertyDouble>();
        case 3:
            return std::make_shared<BrigadierPropertyInteger>();
        case 4:
            return std::make_shared<BrigadierPropertyLong>();
        case 5:
            return std::make_shared<BrigadierPropertyString>();
        case 6:
            return std::make_shared<BrigadierPropertyEntity>();
        case 29:
            return std::make_shared<BrigadierPropertyScoreHolder>();
#if PROTOCOL_VERSION > 760
        case 41:
        case 42:
#endif
        case 43:
        case 44:
            return std::make_shared<BrigadierPropertyResourceOrTag>();
        default:
            return std::make_shared<BrigadierPropertyNone>();
        }
    }
#endif
}
#endif
