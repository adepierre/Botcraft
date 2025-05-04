#if PROTOCOL_VERSION > 388 /* > 1.12.2 */
#pragma once

#include "protocolCraft/BasePacket.hpp"
#include "protocolCraft/Types/NetworkPosition.hpp"

namespace ProtocolCraft
{
    class ServerboundBlockEntityTagQueryPacket : public BasePacket<ServerboundBlockEntityTagQueryPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Block Entity Tag Query";

        SERIALIZED_FIELD(TransactionId, VarInt);
        SERIALIZED_FIELD(Pos, NetworkPosition);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
#endif
