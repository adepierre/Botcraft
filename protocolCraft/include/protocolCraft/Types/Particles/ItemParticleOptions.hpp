#if PROTOCOL_VERSION > 392 /* > 1.12.2 */
#pragma once

#include "protocolCraft/Types/Particles/ParticleOptions.hpp"
#include "protocolCraft/Types/Item/Slot.hpp"

namespace ProtocolCraft
{
    class ItemParticleOptions : public ParticleOptions
    {
        DECLARE_FIELDS(
            (Slot),
            (ItemStack)
        );
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(ItemStack);
    };
}
#endif
