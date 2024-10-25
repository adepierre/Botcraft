#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundGameEventPacket : public BaseMessage<ClientboundGameEventPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Game Event";

        SERIALIZED_FIELD(Type, unsigned char);
        SERIALIZED_FIELD(Param, float);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
