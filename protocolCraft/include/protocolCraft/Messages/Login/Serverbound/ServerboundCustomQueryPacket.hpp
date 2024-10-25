#if PROTOCOL_VERSION > 340 /* > 1.12.2 */ && PROTOCOL_VERSION < 764 /* < 1.20.2 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ServerboundCustomQueryPacket : public BaseMessage<ServerboundCustomQueryPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Custom Query";

        SERIALIZED_FIELD(TransactionId, VarInt);
        SERIALIZED_FIELD(Data, std::optional<Internal::Vector<unsigned char, void, 0>>);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} // ProtocolCraft
#endif
