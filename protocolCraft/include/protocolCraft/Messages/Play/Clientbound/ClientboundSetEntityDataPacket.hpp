#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundSetEntityDataPacket : public BaseMessage<ClientboundSetEntityDataPacket>
    {
    public:

        static constexpr std::string_view packet_name = "Set Entity Data";

        DECLARE_FIELDS(
            (VarInt, Internal::Vector<unsigned char, void, 0>),
            (Id_,    PackedItems)
        );
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(Id_);
        GETTER_SETTER(PackedItems);
    };
} //ProtocolCraft
