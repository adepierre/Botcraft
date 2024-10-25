#if PROTOCOL_VERSION > 754 /* > 1.16.5 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundSetBorderWarningDistancePacket : public BaseMessage<ClientboundSetBorderWarningDistancePacket>
    {
    public:
        static constexpr std::string_view packet_name = "Set Border Warning Distance";

        SERIALIZED_FIELD(WarningBlocks, VarInt);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
#endif
