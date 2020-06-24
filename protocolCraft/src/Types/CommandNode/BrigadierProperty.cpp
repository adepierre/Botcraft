#if PROTOCOL_VERSION > 344
#include "protocolCraft/Types/CommandNode/BrigadierProperty.hpp"

#include "protocolCraft/Types/CommandNode/BrigadierPropertyDouble.hpp"
#include "protocolCraft/Types/CommandNode/BrigadierPropertyFloat.hpp"
#include "protocolCraft/Types/CommandNode/BrigadierPropertyInteger.hpp"
#include "protocolCraft/Types/CommandNode/BrigadierPropertyString.hpp"
#include "protocolCraft/Types/CommandNode/BrigadierPropertyEntity.hpp"
#include "protocolCraft/Types/CommandNode/BrigadierPropertyScoreHolder.hpp"
#include "protocolCraft/Types/CommandNode/BrigadierPropertyRange.hpp"
#include "protocolCraft/Types/CommandNode/BrigadierPropertyNone.hpp"

namespace ProtocolCraft
{
    std::shared_ptr<BrigadierProperty> BrigadierProperty::CreateProperties(const std::string& parser_identifier)
    {
        if (parser_identifier == "brigadier:double")
        {
            return std::shared_ptr<BrigadierPropertyDouble>(new BrigadierPropertyDouble);
        }
        else if (parser_identifier == "brigadier:float")
        {
            return std::shared_ptr<BrigadierPropertyFloat>(new BrigadierPropertyFloat);
        }
        else if (parser_identifier == "brigadier:integer")
        {
            return std::shared_ptr<BrigadierPropertyInteger>(new BrigadierPropertyInteger);
        }
        else if (parser_identifier == "brigadier:string")
        {
            return std::shared_ptr<BrigadierPropertyString>(new BrigadierPropertyString);
        }
        else if (parser_identifier == "minecraft:entity")
        {
            return std::shared_ptr<BrigadierPropertyEntity>(new BrigadierPropertyEntity);
        }
        else if (parser_identifier == "minecraft:score_holder")
        {
            return std::shared_ptr<BrigadierPropertyScoreHolder>(new BrigadierPropertyScoreHolder);
        }
        else if (parser_identifier == "minecraft:range")
        {
            return std::shared_ptr<BrigadierPropertyRange>(new BrigadierPropertyRange);
        }
        else
        {
            return std::shared_ptr<BrigadierPropertyNone>(new BrigadierPropertyNone);
        }
    }
}
#endif
