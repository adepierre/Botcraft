#if PROTOCOL_VERSION > 776 /* > 26.2 */
#pragma once

#include "protocolCraft/NetworkType.hpp"
#include "protocolCraft/Types/AdvancementHolder.hpp"
#include "protocolCraft/Types/Identifier.hpp"

namespace ProtocolCraft
{
    class PositionedAdvancement : public NetworkType
    {
        SERIALIZED_FIELD(Advancement, AdvancementHolder);
        SERIALIZED_FIELD(X, float);
        SERIALIZED_FIELD(Y, float);

        DECLARE_READ_WRITE_SERIALIZE;
    };
}
#endif
