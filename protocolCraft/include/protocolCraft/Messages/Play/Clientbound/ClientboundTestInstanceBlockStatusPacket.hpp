#if PROTOCOL_VERSION > 769 /* > 1.21.4 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/Chat/Chat.hpp"

namespace ProtocolCraft
{
    class ClientboundTestInstanceBlockStatusPacket : public BaseMessage<ClientboundTestInstanceBlockStatusPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Test Instance Block Status";

        SERIALIZED_FIELD(Status, Chat);
        SERIALIZED_FIELD(Size, std::optional<std::array<VarInt, 3>>);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
#endif
