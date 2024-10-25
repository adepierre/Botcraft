#if PROTOCOL_VERSION > 754 /* > 1.16.5 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundSetTitlesAnimationPacket : public BaseMessage<ClientboundSetTitlesAnimationPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Set Titles Animation";

        SERIALIZED_FIELD(FadeIn, int);
        SERIALIZED_FIELD(Stay, int);
        SERIALIZED_FIELD(FadeOut, int);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
#endif
