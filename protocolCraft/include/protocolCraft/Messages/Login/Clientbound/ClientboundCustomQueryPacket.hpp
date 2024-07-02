#if PROTOCOL_VERSION > 340 /* > 1.12.2 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"

#include "protocolCraft/Types/Identifier.hpp"

namespace ProtocolCraft
{
    class ClientboundCustomQueryPacket : public BaseMessage<ClientboundCustomQueryPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Custom Query";

        DECLARE_FIELDS(
            (VarInt,        Identifier, Internal::Vector<unsigned char, void, 0>),
            (TransactionId, Identifier, Data)
        );
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(TransactionId);
        GETTER_SETTER(Identifier);
        GETTER_SETTER(Data);
    };
} //ProtocolCraft
#endif
