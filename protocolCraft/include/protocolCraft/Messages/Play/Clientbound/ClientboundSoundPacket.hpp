#pragma once

#include "protocolCraft/BaseMessage.hpp"

#if PROTOCOL_VERSION > 760 /* > 1.19.2 */
#include "protocolCraft/Types/Holder.hpp"
#include "protocolCraft/Types/Sound/SoundEvent.hpp"
#endif

namespace ProtocolCraft
{
    class ClientboundSoundPacket : public BaseMessage<ClientboundSoundPacket>
    {
    public:

        static constexpr std::string_view packet_name = "Sound";

#if PROTOCOL_VERSION < 759 /* < 1.19 */
        DECLARE_FIELDS(
            (VarInt, VarInt, int, int, int, float,  float),
            (Sound,  Source, X,   Y,   Z,   Volume, Pitch)
        );
#elif PROTOCOL_VERSION < 761 /* < 1.19.3 */
        DECLARE_FIELDS(
            (VarInt, VarInt, int, int, int, float,  float, long long int),
            (Sound,  Source, X,   Y,   Z,   Volume, Pitch, Seed)
        );
#else
        DECLARE_FIELDS(
            (Holder<SoundEvent>, VarInt, int, int, int, float,  float, long long int),
            (Sound,              Source, X,   Y,   Z,   Volume, Pitch, Seed)
        );
#endif
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(Sound);
        GETTER_SETTER(Source);
        GETTER_SETTER(X);
        GETTER_SETTER(Y);
        GETTER_SETTER(Z);
        GETTER_SETTER(Volume);
        GETTER_SETTER(Pitch);
#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
        GETTER_SETTER(Seed);
#endif
    };
} //ProtocolCraft
