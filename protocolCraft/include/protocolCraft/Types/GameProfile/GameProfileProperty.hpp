#pragma once

#include "protocolCraft/NetworkType.hpp"

#include <string>

namespace ProtocolCraft
{
    class GameProfileProperty : public NetworkType
    {
        SERIALIZED_FIELD(Name, std::string);
        SERIALIZED_FIELD(Value, std::string);
        SERIALIZED_FIELD(Signature, std::optional<std::string>);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} // ProtocolCraft
