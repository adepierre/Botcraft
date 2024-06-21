#if PROTOCOL_VERSION > 440 /* > 1.13.2 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"

#if PROTOCOL_VERSION > 760 /* > 1.19.2 */
#include "protocolCraft/Types/Holder.hpp"
#include "protocolCraft/Types/Sound/SoundEvent.hpp"
#endif

namespace ProtocolCraft
{
    class ClientboundSoundEntityPacket : public BaseMessage<ClientboundSoundEntityPacket>
    {
    public:

        static constexpr std::string_view packet_name = "Sound Entity";

#if PROTOCOL_VERSION < 759 /* < 1.19 */
        DECLARE_FIELDS(
            (VarInt, VarInt, VarInt, float,  float),
            (Sound,  Source, Id_,    Volume, Pitch)
        );
#elif PROTOCOL_VERSION < 761 /* < 1.19.3 */
        DECLARE_FIELDS(
            (VarInt, VarInt, VarInt, float,  float, long long int),
            (Sound,  Source, Id_,    Volume, Pitch, Seed)
        );
#else
        DECLARE_FIELDS(
            (Holder<SoundEvent>, VarInt, VarInt, float,  float, long long int),
            (Sound,              Source, Id_,    Volume, Pitch, Seed)
        );
#endif
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(Sound);
        GETTER_SETTER(Source);
        GETTER_SETTER(Id_);
        GETTER_SETTER(Volume);
        GETTER_SETTER(Pitch);
#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
        GETTER_SETTER(Seed);
#endif
    };
} //ProtocolCraft
#endif
