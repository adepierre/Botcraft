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

        SERIALIZED_FIELD(TransactionId, VarInt);
        SERIALIZED_FIELD(Identifier, ProtocolCraft::Identifier);
        SERIALIZED_FIELD(Data, Internal::Vector<unsigned char, void, 0>);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
#endif
