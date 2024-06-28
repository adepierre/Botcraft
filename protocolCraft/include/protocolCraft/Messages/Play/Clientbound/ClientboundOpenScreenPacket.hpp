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
        DECLARE_CONDITION(IsHorse, GetType() == "EntityHorse");
        DECLARE_FIELDS(
            (unsigned char, std::string, Chat,  unsigned char, Internal::Conditioned<int, &THIS::IsHorse>),
            (ContainerId,   Type,        Title, NumberOfSlots, Id_)
        );
#else
        DECLARE_FIELDS(
            (VarInt,      VarInt, Chat),
            (ContainerId, Type,   Title)
        );
#endif
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(ContainerId);
        GETTER_SETTER(Type);
        GETTER_SETTER(Title);
#if PROTOCOL_VERSION < 477 /* < 1.14 */
        GETTER_SETTER(NumberOfSlots);
        GETTER_SETTER(Id_);
#endif
    };
} //ProtocolCraft
