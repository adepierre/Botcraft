#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
#pragma once

#include "protocolCraft/Types/Recipes/SlotDisplayData.hpp"
#if PROTOCOL_VERSION < 777 /* < 26.3 */
#include "protocolCraft/Types/Identifier.hpp"
#else
#include "protocolCraft/Types/HolderSet.hpp"
#endif

namespace ProtocolCraft
{
    class TagSlotDisplay : public SlotDisplayData
    {
#if PROTOCOL_VERSION < 777 /* < 26.3 */
        SERIALIZED_FIELD(Tag, Identifier);
#else
        SERIALIZED_FIELD(Tag, HolderSet);
#endif

        DECLARE_READ_WRITE_SERIALIZE;
    };
}
#endif
