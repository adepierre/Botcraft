#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/NBT/NBT.hpp"
#include "protocolCraft/Types/NetworkPosition.hpp"

namespace ProtocolCraft
{
    class ClientboundBlockEntityDataPacket : public BaseMessage<ClientboundBlockEntityDataPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Block Entity Data";

        SERIALIZED_FIELD(Pos, NetworkPosition);
#if PROTOCOL_VERSION < 757 /* < 1.18 */
        SERIALIZED_FIELD(Type, unsigned char);
#else
        SERIALIZED_FIELD(Type, VarInt);
#endif
        SERIALIZED_FIELD(Tag, NBT::UnnamedValue);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
