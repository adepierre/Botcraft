#if PROTOCOL_VERSION > 767 /* > 1.21.1 */
#pragma once
#include "protocolCraft/Types/Components/Subtypes/ConsumeEffects/ConsumeEffectData.hpp"
#include "protocolCraft/Types/Sound/SoundEvent.hpp"
#include "protocolCraft/Types/Holder.hpp"

namespace ProtocolCraft
{
    namespace Components
    {
        class PlaySoundConsumeEffect : public ConsumeEffectData
        {
            SERIALIZED_FIELD(Sound, Holder<SoundEvent>);

            DECLARE_READ_WRITE_SERIALIZE;
        };
    }
}
#endif
