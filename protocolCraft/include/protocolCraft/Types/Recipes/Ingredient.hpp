#if PROTOCOL_VERSION > 347 /* > 1.12.2 */
#pragma once

#include "protocolCraft/NetworkType.hpp"
#include "protocolCraft/Types/Item/Slot.hpp"

namespace ProtocolCraft
{
    class Ingredient : public NetworkType
    {
        DECLARE_FIELDS(
            (std::vector<Slot>),
            (Items)
        );
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(Items);
    };
}
#endif
