#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
#pragma once
#include "protocolCraft/Types/Components/DataComponentType.hpp"
#include "protocolCraft/Types/Identifier.hpp"
#include "protocolCraft/Types/Holder.hpp"
#include "protocolCraft/Types/Sound/SoundEvent.hpp"
#include "protocolCraft/Types/HolderSet.hpp"

#include <optional>

namespace ProtocolCraft
{
    namespace Components
    {
        class DataComponentTypeEquippable : public DataComponentType
        {
            SERIALIZED_FIELD(Slot, VarInt);
            SERIALIZED_FIELD(EquipSound, Holder<SoundEvent>);
#if PROTOCOL_VERSION < 769 /* < 1.21.4 */
            SERIALIZED_FIELD(Model, std::optional<Identifier>);
#else
            SERIALIZED_FIELD(AssetId, std::optional<Identifier>);
#endif
            SERIALIZED_FIELD(CameraOverlay, std::optional<Identifier>);
            SERIALIZED_FIELD(AllowedEntities, std::optional<HolderSet>);
            SERIALIZED_FIELD(Dispensable, bool);
            SERIALIZED_FIELD(Swappable, bool);
            SERIALIZED_FIELD(DamageOnHurt, bool);
#if PROTOCOL_VERSION > 770 /* > 1.21.5 */
            SERIALIZED_FIELD(EquipOnInteract, bool);
            SERIALIZED_FIELD(CanBeSheared, bool);
            SERIALIZED_FIELD(ShearingSound, Holder<SoundEvent>);
#endif

            DECLARE_READ_WRITE_SERIALIZE;
        };
    }
}
#endif
