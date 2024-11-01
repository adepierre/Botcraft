#if PROTOCOL_VERSION > 347 /* > 1.12.2 */
#pragma once

#include "protocolCraft/NetworkType.hpp"
#if PROTOCOL_VERSION < 768 /* < 1.21.2 */
#include "protocolCraft/Types/Item/Slot.hpp"
#else
#include "protocolCraft/Types/HolderSet.hpp"
#endif

namespace ProtocolCraft
{
    class Ingredient : public NetworkType
    {
#if PROTOCOL_VERSION < 768 /* < 1.21.2 */
        SERIALIZED_FIELD(Items, std::vector<Slot>);
#else
        SERIALIZED_FIELD(Items, HolderSet);
#endif

        DECLARE_READ_WRITE_SERIALIZE;
    };
}
#endif
