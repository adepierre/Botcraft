#if PROTOCOL_VERSION > 763 /* > 1.20.1 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ServerboundCustomQueryAnswerPacket : public BaseMessage<ServerboundCustomQueryAnswerPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Custom Query Answer";

        SERIALIZED_FIELD(TransactionId, VarInt);
        SERIALIZED_FIELD(Payload, std::optional<Internal::Vector<unsigned char, void, 0>>);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} // ProtocolCraft
#endif
