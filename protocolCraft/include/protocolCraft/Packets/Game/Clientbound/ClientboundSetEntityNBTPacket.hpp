#if PROTOCOL_VERSION < 107 /* < 1.9 */
#pragma once

#include "protocolCraft/BasePacket.hpp"
#include "protocolCraft/Types/NBT/NBT.hpp"

namespace ProtocolCraft
{
    class ClientboundSetEntityNBTPacket : public BasePacket<ClientboundSetEntityNBTPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Set Entity NBT";

        SERIALIZED_FIELD(EntityId, VarInt);
        SERIALIZED_FIELD(Data, NBT::UnnamedValue);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
#endif
