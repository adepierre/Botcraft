#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
#pragma once

#include "protocolCraft/Types/Recipes/SlotDisplayData.hpp"
#include "protocolCraft/Types/Item/Slot.hpp"

namespace ProtocolCraft
{
    class ItemStackSlotDisplay : public SlotDisplayData
    {
        SERIALIZED_FIELD(Stack, Slot);

        DECLARE_READ_WRITE_SERIALIZE;
    };
}
#endif
