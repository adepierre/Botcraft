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

#if PROTOCOL_VERSION < 757 /* < 1.18 */
        DECLARE_FIELDS(
            (NetworkPosition, unsigned char, NBT::UnnamedValue),
            (Pos,             Type,          Tag)
        );
#else
        DECLARE_FIELDS(
            (NetworkPosition, VarInt, NBT::UnnamedValue),
            (Pos,             Type,   Tag)
        );
#endif
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(Pos);
        GETTER_SETTER(Type);
        GETTER_SETTER(Tag);
    };
} //ProtocolCraft
