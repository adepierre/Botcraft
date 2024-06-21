#if PROTOCOL_VERSION < 761 /* < 1.19.3 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundCustomSoundPacket : public BaseMessage<ClientboundCustomSoundPacket>
    {
    public:

        static constexpr std::string_view packet_name = "Custom Sound";

#if PROTOCOL_VERSION < 759 /* < 1.19 */
        DECLARE_FIELDS(
            (std::string, VarInt, int, int, int, float,  float),
            (Name_,       Source, X,   Y,   Z,   Volume, Pitch)
        );
#else
        DECLARE_FIELDS(
            (std::string, VarInt, int, int, int, float,  float, long long int),
            (Name_,       Source, X,   Y,   Z,   Volume, Pitch, Seed)
        );
#endif
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(Name_);
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
#endif
