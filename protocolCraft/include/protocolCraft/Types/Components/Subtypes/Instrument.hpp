#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#pragma once
#include "protocolCraft/NetworkType.hpp"
#include "protocolCraft/Types/Holder.hpp"
#include "protocolCraft/Types/Sound/SoundEvent.hpp"
#include "protocolCraft/Types/Chat/Chat.hpp"

namespace ProtocolCraft
{
    namespace Components
    {
        class Instrument : public NetworkType
        {
            SERIALIZED_FIELD(SoundEvent, Holder<ProtocolCraft::SoundEvent>);
            SERIALIZED_FIELD(UseDuration, float);
            SERIALIZED_FIELD(Range, float);
            SERIALIZED_FIELD(Description, Chat);

            DECLARE_READ_WRITE_SERIALIZE;
        };
    }
}
#endif
