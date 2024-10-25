#if PROTOCOL_VERSION > 754 /* > 1.16.5 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundInitializeBorderPacket : public BaseMessage<ClientboundInitializeBorderPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Initialize Border";

        SERIALIZED_FIELD(NewCenterX, double);
        SERIALIZED_FIELD(NewCenterZ, double);
        SERIALIZED_FIELD(OldSize, double);
        SERIALIZED_FIELD(NewSize, double);
        SERIALIZED_FIELD(LerpTime, VarLong);
        SERIALIZED_FIELD(NewAbsoluteMaxSize, VarInt);
        SERIALIZED_FIELD(WarningBlocks, VarInt);
        SERIALIZED_FIELD(WarningTime, VarInt);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
#endif
