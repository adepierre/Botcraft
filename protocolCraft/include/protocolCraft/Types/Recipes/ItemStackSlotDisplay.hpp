#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
#pragma once

#include "protocolCraft/Types/Recipes/SlotDisplayData.hpp"
#if PROTOCOL_VERSION < 775 /* < 26.1 */
#include "protocolCraft/Types/Item/Slot.hpp"
#else
#include "protocolCraft/Types/Item/ItemStackTemplate.hpp"
#endif

namespace ProtocolCraft
{
    class ItemStackSlotDisplay : public SlotDisplayData
    {
#if PROTOCOL_VERSION < 775 /* < 26.1 */
        SERIALIZED_FIELD(Stack, Slot);
#else
        SERIALIZED_FIELD(Stack, ItemStackTemplate);
#endif

        DECLARE_READ_WRITE_SERIALIZE;
    };
}
#endif
