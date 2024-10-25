#if PROTOCOL_VERSION > 347 /* > 1.12.2 */
#pragma once

#include "protocolCraft/NetworkType.hpp"
#include "protocolCraft/Types/Item/Slot.hpp"

namespace ProtocolCraft
{
    class Ingredient : public NetworkType
    {
        SERIALIZED_FIELD(Items, std::vector<Slot>);

        DECLARE_READ_WRITE_SERIALIZE;
    };
}
#endif
