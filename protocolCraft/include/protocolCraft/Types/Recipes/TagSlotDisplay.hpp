#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
#pragma once

#include "protocolCraft/Types/Recipes/SlotDisplayData.hpp"
#include "protocolCraft/Types/Identifier.hpp"

namespace ProtocolCraft
{
    class TagSlotDisplay : public SlotDisplayData
    {
        SERIALIZED_FIELD(Tag, Identifier);

        DECLARE_READ_WRITE_SERIALIZE;
    };
}
#endif
