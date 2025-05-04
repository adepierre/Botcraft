#pragma once

#include "protocolCraft/BasePacket.hpp"

#if PROTOCOL_VERSION > 760 /* > 1.19.2 */
#include "protocolCraft/Types/Holder.hpp"
#include "protocolCraft/Types/Sound/SoundEvent.hpp"
#endif

namespace ProtocolCraft
{
    class ClientboundSoundPacket : public BasePacket<ClientboundSoundPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Sound";

#if PROTOCOL_VERSION < 761 /* < 1.19.3 */
        SERIALIZED_FIELD(Sound, VarInt);
#else
        SERIALIZED_FIELD(Sound, Holder<SoundEvent>);
#endif
        SERIALIZED_FIELD(Source, VarInt);
        SERIALIZED_FIELD(X, int);
        SERIALIZED_FIELD(Y, int);
        SERIALIZED_FIELD(Z, int);
        SERIALIZED_FIELD(Volume, float);
        SERIALIZED_FIELD(Pitch, float);
#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
        SERIALIZED_FIELD(Seed, long long int);
#endif

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
