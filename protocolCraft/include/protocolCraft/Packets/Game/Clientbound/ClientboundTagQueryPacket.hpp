#if PROTOCOL_VERSION > 388 /* > 1.12.2 */
#pragma once

#include "protocolCraft/BasePacket.hpp"
#include "protocolCraft/Types/NBT/NBT.hpp"

namespace ProtocolCraft
{
    class ClientboundTagQueryPacket : public BasePacket<ClientboundTagQueryPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Tag Query";

        SERIALIZED_FIELD(TransactionId, VarInt);
        SERIALIZED_FIELD(Tag, NBT::UnnamedValue);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
#endif
