#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundGameEventPacket : public BaseMessage<ClientboundGameEventPacket>
    {
    public:

        static constexpr std::string_view packet_name = "Game Event";

        DECLARE_FIELDS(
            (unsigned char, float),
            (Type,          Param)
        );
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(Type);
        GETTER_SETTER(Param);
    };
} //ProtocolCraft
