#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#pragma once
#include "protocolCraft/NetworkType.hpp"
#include "protocolCraft/Types/Components/DataComponents.hpp"

namespace ProtocolCraft
{
    class ItemCost : public NetworkType
    {
        DECLARE_FIELDS_TYPES(VarInt, VarInt, Components::DataComponentPredicate);
        DECLARE_FIELDS_NAMES(ItemID, Count,  Components);
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(ItemID);
        GETTER_SETTER(Count);
        GETTER_SETTER(Components);
    };
} // ProtocolCraft
#endif
