#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ServerboundKeepAlivePacket : public BaseMessage<ServerboundKeepAlivePacket>
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
