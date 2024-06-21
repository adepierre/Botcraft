#if PROTOCOL_VERSION > 388 /* > 1.12.2 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/NBT/NBT.hpp"

namespace ProtocolCraft
{
    class ClientboundTagQueryPacket : public BaseMessage<ClientboundTagQueryPacket>
    {
    public:

        static constexpr std::string_view packet_name = "Tag Query";

        DECLARE_FIELDS(
            (VarInt,        NBT::UnnamedValue),
            (TransactionId, Tag)
        );
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(TransactionId);
        GETTER_SETTER(Tag);
    };
} //ProtocolCraft
#endif
