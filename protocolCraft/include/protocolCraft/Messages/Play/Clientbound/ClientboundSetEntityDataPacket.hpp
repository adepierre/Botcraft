#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundSetEntityDataPacket : public BaseMessage<ClientboundSetEntityDataPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Set Entity Data";

        SERIALIZED_FIELD(Id_, VarInt);
        SERIALIZED_FIELD(PackedItems, Internal::Vector<unsigned char, void, 0>);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
