#if PROTOCOL_VERSION < 759 /* < 1.19 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/NetworkPosition.hpp"

namespace ProtocolCraft
{
    class ClientboundAddPaintingPacket : public BaseMessage<ClientboundAddPaintingPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Add Painting";

        SERIALIZED_FIELD(Id_, VarInt);
        SERIALIZED_FIELD(Uuid, UUID);
#if PROTOCOL_VERSION < 393 /* < 1.13 */
        SERIALIZED_FIELD(Title, std::string);
#else
        SERIALIZED_FIELD(Motive, VarInt);
#endif
        SERIALIZED_FIELD(Pos, NetworkPosition);
        SERIALIZED_FIELD(Direction, char);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
#endif
