#if PROTOCOL_VERSION > 769 /* > 1.21.4 */
#pragma once
#include "protocolCraft/Types/Components/DataComponentType.hpp"
#include "protocolCraft/Types/Identifier.hpp"
#include "protocolCraft/Types/Holder.hpp"
#include "protocolCraft/Types/Components/Subtypes/DamageReduction.hpp"
#include "protocolCraft/Types/Components/Subtypes/ItemDamageFunction.hpp"

#include <optional>

namespace ProtocolCraft
{
    namespace Components
    {
        class DataComponentTypeBlocksAttacks : public DataComponentType
        {
            SERIALIZED_FIELD(BlockDelaySeconds, float);
            SERIALIZED_FIELD(DisableCooldownScale, float);
            SERIALIZED_FIELD(DamageReductions, std::vector<DamageReduction>);
            SERIALIZED_FIELD(ItemDamage, ItemDamageFunction);
            SERIALIZED_FIELD(BypassedBy, std::optional<Identifier>);
            SERIALIZED_FIELD(BlockSound, std::optional<Holder<SoundEvent>>);
            SERIALIZED_FIELD(DisableSound, std::optional<Holder<SoundEvent>>);

            DECLARE_READ_WRITE_SERIALIZE;
        };
    }
}
#endif
