#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundSetTimePacket : public BaseMessage<ClientboundSetTimePacket>
    {
    public:

        static constexpr std::string_view packet_name = "Set Time";

        DECLARE_FIELDS(
            (long long int, long long int),
            (GameTime,      DayTime)
        );
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(GameTime);
        GETTER_SETTER(DayTime);
    };
} //ProtocolCraft
