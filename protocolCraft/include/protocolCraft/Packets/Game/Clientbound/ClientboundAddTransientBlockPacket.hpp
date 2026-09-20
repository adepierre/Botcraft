#if PROTOCOL_VERSION > 776 /* > 26.2 */
#pragma once
#include "protocolCraft/BasePacket.hpp"

#include "protocolCraft/Types/NetworkPosition.hpp"

namespace ProtocolCraft
{
    class ClientboundAddTransientBlockPacket : public BasePacket<ClientboundAddTransientBlockPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Add Transient Block";

        SERIALIZED_FIELD(Pos, NetworkPosition);
        SERIALIZED_FIELD(BlockState, VarInt);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
#endif
