#if PROTOCOL_VERSION > 440 /* > 1.13.2 */
#pragma once

#include "protocolCraft/BasePacket.hpp"

#if PROTOCOL_VERSION > 760 /* > 1.19.2 */
#include "protocolCraft/Types/Holder.hpp"
#include "protocolCraft/Types/Sound/SoundEvent.hpp"
#endif

namespace ProtocolCraft
{
    class ClientboundSoundEntityPacket : public BasePacket<ClientboundSoundEntityPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Sound Entity";

#if PROTOCOL_VERSION < 761 /* < 1.19.3 */
        SERIALIZED_FIELD(Sound, VarInt);
#else
        SERIALIZED_FIELD(Sound, Holder<SoundEvent>);
#endif
        SERIALIZED_FIELD(Source, VarInt);
        SERIALIZED_FIELD(Id_, VarInt);
        SERIALIZED_FIELD(Volume, float);
        SERIALIZED_FIELD(Pitch, float);
#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
        SERIALIZED_FIELD(Seed, long long int);
#endif

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
#endif
