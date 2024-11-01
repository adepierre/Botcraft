#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
#pragma once

#include "protocolCraft/Types/Recipes/SlotDisplayData.hpp"

namespace ProtocolCraft
{
    class ItemSlotDisplay : public SlotDisplayData
    {
        SERIALIZED_FIELD(Item, VarInt);

        DECLARE_READ_WRITE_SERIALIZE;
    };
}
#endif
