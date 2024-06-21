#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundKeepAlivePacket : public BaseMessage<ClientboundKeepAlivePacket>
    {
    public:

        static constexpr std::string_view packet_name = "Keep Alive";

        DECLARE_FIELDS(
            (long long int),
            (Id_)
        );
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(Id_);
    };
} //ProtocolCraft
