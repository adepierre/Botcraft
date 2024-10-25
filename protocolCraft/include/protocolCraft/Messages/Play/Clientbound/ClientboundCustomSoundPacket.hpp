#if PROTOCOL_VERSION < 761 /* < 1.19.3 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundCustomSoundPacket : public BaseMessage<ClientboundCustomSoundPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Custom Sound";

        SERIALIZED_FIELD(Name_, std::string);
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
#endif
