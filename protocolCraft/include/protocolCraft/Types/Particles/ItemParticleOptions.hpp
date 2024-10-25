#if PROTOCOL_VERSION > 392 /* > 1.12.2 */
#pragma once

#include "protocolCraft/Types/Particles/ParticleOptions.hpp"
#include "protocolCraft/Types/Item/Slot.hpp"

namespace ProtocolCraft
{
    class ItemParticleOptions : public ParticleOptions
    {
        SERIALIZED_FIELD(ItemStack, Slot);

        DECLARE_READ_WRITE_SERIALIZE;
    };
}
#endif
