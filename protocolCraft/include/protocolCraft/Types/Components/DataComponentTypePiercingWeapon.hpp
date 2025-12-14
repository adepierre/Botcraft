#if PROTOCOL_VERSION > 773 /* > 1.21.10 */
#pragma once
#include "protocolCraft/Types/Components/DataComponentType.hpp"
#include "protocolCraft/Types/Sound/SoundEvent.hpp"
#include "protocolCraft/Types/Holder.hpp"

#include <optional>

namespace ProtocolCraft
{
    namespace Components
    {
        class DataComponentTypePiercingWeapon : public DataComponentType
        {
            SERIALIZED_FIELD(DealsKnockback, bool);
            SERIALIZED_FIELD(Dismounts, bool);
            SERIALIZED_FIELD(Sound, std::optional<Holder<SoundEvent>>);
            SERIALIZED_FIELD(HitSound, std::optional<Holder<SoundEvent>>);

            DECLARE_READ_WRITE_SERIALIZE;
        };
    }
}
#endif
