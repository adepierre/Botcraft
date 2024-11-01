#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
#pragma once
#include "protocolCraft/Types/Components/DataComponentType.hpp"
#include "protocolCraft/Types/Holder.hpp"
#include "protocolCraft/Types/Sound/SoundEvent.hpp"
#include "protocolCraft/Types/Components/Subtypes/ConsumeEffects/ConsumeEffect.hpp"

namespace ProtocolCraft
{
    namespace Components
    {
        class DataComponentTypeConsumable : public DataComponentType
        {
            SERIALIZED_FIELD(ConsumeSeconds, float);
            SERIALIZED_FIELD(Animation, VarInt);
            SERIALIZED_FIELD(Sound, Holder<SoundEvent>);
            SERIALIZED_FIELD(HasConsumeParticles, bool);
            SERIALIZED_FIELD(OnConsumeEffects, std::vector<ConsumeEffect>);

            DECLARE_READ_WRITE_SERIALIZE;
        };
    }
}
#endif
