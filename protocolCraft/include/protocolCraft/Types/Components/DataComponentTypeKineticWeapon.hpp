#if PROTOCOL_VERSION > 773 /* > 1.21.10 */
#pragma once
#include "protocolCraft/Types/Components/DataComponentType.hpp"
#include "protocolCraft/Types/Components/Subtypes/KineticWeaponCondition.hpp"
#include "protocolCraft/Types/Sound/SoundEvent.hpp"
#include "protocolCraft/Types/Holder.hpp"

#include <optional>

namespace ProtocolCraft
{
    namespace Components
    {
        class DataComponentTypeKineticWeapon : public DataComponentType
        {
            SERIALIZED_FIELD(ContactCooldownTicks, VarInt);
            SERIALIZED_FIELD(DelayTicks, VarInt);
            SERIALIZED_FIELD(DismountConditions, std::optional<KineticWeaponCondition>);
            SERIALIZED_FIELD(KnockbackConditions, std::optional<KineticWeaponCondition>);
            SERIALIZED_FIELD(DamageConditions, std::optional<KineticWeaponCondition>);
            SERIALIZED_FIELD(ForwardMovement, float);
            SERIALIZED_FIELD(DamageMultiplier, float);
            SERIALIZED_FIELD(Sound, std::optional<Holder<SoundEvent>>);
            SERIALIZED_FIELD(HitSound, std::optional<Holder<SoundEvent>>);

            DECLARE_READ_WRITE_SERIALIZE;
        };
    }
}
#endif
