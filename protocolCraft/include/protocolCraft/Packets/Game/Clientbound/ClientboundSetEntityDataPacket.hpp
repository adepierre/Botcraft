#pragma once

#include "protocolCraft/BasePacket.hpp"

namespace ProtocolCraft
{
    class ClientboundSetEntityDataPacket : public BasePacket<ClientboundSetEntityDataPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Set Entity Data";

        SERIALIZED_FIELD(EntityId, VarInt);
        SERIALIZED_FIELD(PackedItems, Internal::Vector<unsigned char, void, 0>);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
