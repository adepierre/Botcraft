#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#pragma once
#include "protocolCraft/NetworkType.hpp"
#include "protocolCraft/Types/Components/DataComponents.hpp"

namespace ProtocolCraft
{
    class ItemCost : public NetworkType
    {
        SERIALIZED_FIELD(ItemId, VarInt);
        SERIALIZED_FIELD(Count, VarInt);
        SERIALIZED_FIELD(Components, Components::DataComponentPredicate);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} // ProtocolCraft
#endif
