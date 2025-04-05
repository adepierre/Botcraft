#if PROTOCOL_VERSION > 766 /* > 1.20.6 */
#pragma once
#include "protocolCraft/NetworkType.hpp"
#include "protocolCraft/Types/Holder.hpp"
#include "protocolCraft/Types/Sound/SoundEvent.hpp"
#include "protocolCraft/Types/Chat/Chat.hpp"

namespace ProtocolCraft
{
    namespace Components
    {
        class JukeboxSong : public NetworkType
        {
            SERIALIZED_FIELD(SoundEvent, Holder<ProtocolCraft::SoundEvent>);
            SERIALIZED_FIELD(Description, Chat);
            SERIALIZED_FIELD(LengthInSeconds, float);
            SERIALIZED_FIELD(ComparatorOutput, VarInt);

            DECLARE_READ_WRITE_SERIALIZE;
        };
    }
}
#endif
