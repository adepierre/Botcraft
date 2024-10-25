#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/NetworkPosition.hpp"

namespace ProtocolCraft
{
    class ClientboundLevelEventPacket : public BaseMessage<ClientboundLevelEventPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Level Event";

        SERIALIZED_FIELD(Type, int);
        SERIALIZED_FIELD(Pos, NetworkPosition);
        SERIALIZED_FIELD(Data, int);
        SERIALIZED_FIELD(GlobalEvent, bool);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
