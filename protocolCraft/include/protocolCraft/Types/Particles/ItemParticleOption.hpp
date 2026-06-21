#if PROTOCOL_VERSION > 392 /* > 1.12.2 */
#pragma once

#include "protocolCraft/Types/Particles/ParticleOption.hpp"
#if PROTOCOL_VERSION < 775 /* < 26.1 */
#include "protocolCraft/Types/Item/Slot.hpp"
#else
#include "protocolCraft/Types/Item/ItemStackTemplate.hpp"
#endif

namespace ProtocolCraft
{
    class ItemParticleOption : public ParticleOption
    {
#if PROTOCOL_VERSION < 775 /* < 26.1 */
        SERIALIZED_FIELD(ItemStack, Slot);
#else
        SERIALIZED_FIELD(ItemStack, ItemStackTemplate);
#endif

        DECLARE_READ_WRITE_SERIALIZE;
    };
}
#endif
