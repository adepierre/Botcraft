#if PROTOCOL_VERSION > 763 /* > 1.20.1 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ServerboundCustomQueryAnswerPacket : public BaseMessage<ServerboundCustomQueryAnswerPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Custom Query Answer";

        DECLARE_FIELDS(
            (VarInt,        std::optional<Internal::Vector<unsigned char, void, 0>>),
            (TransactionId, Payload)
        );
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(TransactionId);
        GETTER_SETTER(Payload);
    };
} // ProtocolCraft
#endif
