#if PROTOCOL_VERSION > 754 /* > 1.16.5 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundSetTitlesAnimationPacket : public BaseMessage<ClientboundSetTitlesAnimationPacket>
    {
    public:

        static constexpr std::string_view packet_name = "Set Titles Animation";

        DECLARE_FIELDS(
            (int, int, int),
            (FadeIn, Stay, FadeOut)
        );
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(FadeIn);
        GETTER_SETTER(Stay);
        GETTER_SETTER(FadeOut);
    };
} //ProtocolCraft
#endif
