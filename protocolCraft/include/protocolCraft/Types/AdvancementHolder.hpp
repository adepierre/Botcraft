#pragma once

#include "protocolCraft/NetworkType.hpp"
#include "protocolCraft/Types/Advancement.hpp"
#include "protocolCraft/Types/Identifier.hpp"

namespace ProtocolCraft
{
    class AdvancementHolder : public NetworkType
    {
        SERIALIZED_FIELD(Id, Identifier);
        SERIALIZED_FIELD(Value, Advancement);

        DECLARE_READ_WRITE_SERIALIZE;
    };
}
