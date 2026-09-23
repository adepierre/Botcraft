#pragma once

#include "protocolCraft/BasePacket.hpp"

#if PROTOCOL_VERSION > 760 /* > 1.19.2 */
#include "protocolCraft/Types/Holder.hpp"
#include "protocolCraft/Types/Sound/SoundEvent.hpp"
#endif

#if PROTOCOL_VERSION < 107 /* < 1.9 */
#include <string>
#endif

namespace ProtocolCraft
{
    class ClientboundSoundPacket : public BasePacket<ClientboundSoundPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Sound";

#if PROTOCOL_VERSION < 107 /* < 1.9 */
        SERIALIZED_FIELD(Sound, std::string);
#elif PROTOCOL_VERSION < 761 /* < 1.19.3 */
        SERIALIZED_FIELD(Sound, VarInt);
#else
        SERIALIZED_FIELD(Sound, Holder<SoundEvent>);
#endif
#if PROTOCOL_VERSION > 47 /* > 1.8.9 */
        SERIALIZED_FIELD(Source, VarInt);
#endif
        SERIALIZED_FIELD(X, int);
        SERIALIZED_FIELD(Y, int);
        SERIALIZED_FIELD(Z, int);
        SERIALIZED_FIELD(Volume, float);
#if PROTOCOL_VERSION < 210 /* < 1.10 */
        SERIALIZED_FIELD(Pitch, unsigned char);
#else
        SERIALIZED_FIELD(Pitch, float);
#endif
#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
        SERIALIZED_FIELD(Seed, long long int);
#endif

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
