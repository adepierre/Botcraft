#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundSetTimePacket : public BaseMessage<ClientboundSetTimePacket>
    {
    public:
        static constexpr std::string_view packet_name = "Set Time";

        SERIALIZED_FIELD(GameTime, long long int);
        SERIALIZED_FIELD(DayTime, long long int);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
