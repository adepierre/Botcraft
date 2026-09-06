#if PROTOCOL_VERSION < 338 /* < 1.12.1 */
#pragma once

#include "protocolCraft/NetworkType.hpp"
#include "protocolCraft/Types/Item/Slot.hpp"

namespace ProtocolCraft
{
    class RecipePlacementItemMove : public NetworkType
    {
        SERIALIZED_FIELD(Stack, Slot);
        SERIALIZED_FIELD(Src, unsigned char);
        SERIALIZED_FIELD(Dst, unsigned char);

        DECLARE_READ_WRITE_SERIALIZE;
    };
}
#endif
