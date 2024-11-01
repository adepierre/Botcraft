#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
#pragma once

#include "protocolCraft/Types/Recipes/SlotDisplayData.hpp"
#include "protocolCraft/Types/Recipes/SlotDisplay.hpp"

namespace ProtocolCraft
{
    class WithRemainderSlotDisplay : public SlotDisplayData
    {
        SERIALIZED_FIELD(Input, SlotDisplay);
        SERIALIZED_FIELD(Remainder, SlotDisplay);

        DECLARE_READ_WRITE_SERIALIZE;
    };
}
#endif
