#pragma once

#include "protocolCraft/NetworkType.hpp"

#include <string>

namespace ProtocolCraft
{
    class GameProfileProperty : public NetworkType
    {
        DECLARE_FIELDS_TYPES(std::string, std::string, std::optional<std::string>);
        DECLARE_FIELDS_NAMES(Name,        Value,       Signature);
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(Name);
        GETTER_SETTER(Value);
        GETTER_SETTER(Signature);
    };
} // ProtocolCraft
