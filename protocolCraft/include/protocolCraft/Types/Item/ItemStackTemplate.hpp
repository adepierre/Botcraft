#if PROTOCOL_VERSION > 774 /* > 1.21.11 */
#pragma once

#include "protocolCraft/NetworkType.hpp"
#include "protocolCraft/Types/Components/DataComponents.hpp"

namespace ProtocolCraft
{
    class ItemStackTemplate : public NetworkType
    {
        SERIALIZED_FIELD(Item, VarInt);
        SERIALIZED_FIELD(Count, VarInt);
        SERIALIZED_FIELD(Components, Components::DataComponentPatch);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} // ProtocolCraft
#endif
