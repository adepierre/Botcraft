#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/NetworkPosition.hpp"

namespace ProtocolCraft
{
    class ClientboundLevelEventPacket : public BaseMessage<ClientboundLevelEventPacket>
    {
    public:

        static constexpr std::string_view packet_name = "Level Event";

        DECLARE_FIELDS(
            (int,  NetworkPosition, int,  bool),
            (Type, Pos,             Data, GlobalEvent)
        );
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(Type);
        GETTER_SETTER(Pos);
        GETTER_SETTER(Data);
        GETTER_SETTER(GlobalEvent);
    };
} //ProtocolCraft
