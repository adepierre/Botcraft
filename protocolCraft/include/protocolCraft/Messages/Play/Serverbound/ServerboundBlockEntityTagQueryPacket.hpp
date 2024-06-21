#if PROTOCOL_VERSION > 388 /* > 1.12.2 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/NetworkPosition.hpp"

namespace ProtocolCraft
{
    class ServerboundBlockEntityTagQueryPacket : public BaseMessage<ServerboundBlockEntityTagQueryPacket>
    {
    public:

        static constexpr std::string_view packet_name = "Block Entity Tag Query";

        DECLARE_FIELDS(
            (VarInt,        NetworkPosition),
            (TransactionId, Pos)
        );
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(TransactionId);
        GETTER_SETTER(Pos);
    };
} //ProtocolCraft
#endif
