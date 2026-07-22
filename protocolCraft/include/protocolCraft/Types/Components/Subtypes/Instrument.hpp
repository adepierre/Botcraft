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
#if PROTOCOL_VERSION < 768 /* < 1.21.2 */
            SERIALIZED_FIELD(UseDuration, VarInt);
#else
            SERIALIZED_FIELD(UseDuration, float);
#endif
            SERIALIZED_FIELD(Range, float);
            SERIALIZED_FIELD(Description, Chat);

            DECLARE_READ_WRITE_SERIALIZE;
        };
    }
}
#endif
