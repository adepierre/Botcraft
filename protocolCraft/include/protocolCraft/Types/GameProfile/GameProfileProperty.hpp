#pragma once

#include "protocolCraft/NetworkType.hpp"

#include <string>

namespace ProtocolCraft
{
    class GameProfileProperty : public NetworkType
    {
        DECLARE_FIELDS(
            (std::string, std::string, std::optional<std::string>),
            (Name,        Value,       Signature)
        );
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(Name);
        GETTER_SETTER(Value);
        GETTER_SETTER(Signature);
    };
} // ProtocolCraft
