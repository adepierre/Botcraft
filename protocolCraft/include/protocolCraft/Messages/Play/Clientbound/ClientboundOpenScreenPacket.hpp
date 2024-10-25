#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/Chat/Chat.hpp"

namespace ProtocolCraft
{
    class ClientboundOpenScreenPacket : public BaseMessage<ClientboundOpenScreenPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Open Screen";

#if PROTOCOL_VERSION < 477 /* < 1.14 */
        DEFINE_CONDITION(IsHorse, GetType() == "EntityHorse");
        SERIALIZED_FIELD(ContainerId, unsigned char);
        SERIALIZED_FIELD(Type, std::string);
        SERIALIZED_FIELD(Title, Chat);
        SERIALIZED_FIELD(NumberOfSlots, unsigned char);
        SERIALIZED_FIELD(Id_, Internal::Conditioned<int, &THIS::IsHorse>);
#else
        SERIALIZED_FIELD(ContainerId, VarInt);
        SERIALIZED_FIELD(Type, VarInt);
        SERIALIZED_FIELD(Title, Chat);
#endif

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
