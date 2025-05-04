#if PROTOCOL_VERSION > 344 /* > 1.12.2 */
#pragma once

#include "protocolCraft/BasePacket.hpp"
#include "protocolCraft/Types/CommandNode/CommandNode.hpp"

namespace ProtocolCraft
{
    class ClientboundCommandsPacket : public BasePacket<ClientboundCommandsPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Commands";

        SERIALIZED_FIELD(Nodes, std::vector<CommandNode>);
        SERIALIZED_FIELD(RootIndex, VarInt);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
#endif
