#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
#pragma once

#include "protocolCraft/Types/Recipes/SlotDisplayData.hpp"
#include "protocolCraft/Types/Recipes/SlotDisplay.hpp"

namespace ProtocolCraft
{
    class SmithingTrimDemoSlotDisplay : public SlotDisplayData
    {
        SERIALIZED_FIELD(Base, SlotDisplay);
        SERIALIZED_FIELD(Material, SlotDisplay);
        SERIALIZED_FIELD(Pattern, SlotDisplay);

        DECLARE_READ_WRITE_SERIALIZE;
    };
}
#endif
