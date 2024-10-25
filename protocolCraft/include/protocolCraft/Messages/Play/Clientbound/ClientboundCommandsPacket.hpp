#if PROTOCOL_VERSION > 344 /* > 1.12.2 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/CommandNode/CommandNode.hpp"

namespace ProtocolCraft
{
    class ClientboundCommandsPacket : public BaseMessage<ClientboundCommandsPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Commands";

        SERIALIZED_FIELD(Nodes, std::vector<CommandNode>);
        SERIALIZED_FIELD(RootIndex, VarInt);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
#endif
