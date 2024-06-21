#if PROTOCOL_VERSION > 754 /* > 1.16.5 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundInitializeBorderPacket : public BaseMessage<ClientboundInitializeBorderPacket>
    {
    public:

        static constexpr std::string_view packet_name = "Initialize Border";

        DECLARE_FIELDS(
            (double,     double,     double,  double,  VarLong,  VarInt,             VarInt,        VarInt),
            (NewCenterX, NewCenterZ, OldSize, NewSize, LerpTime, NewAbsoluteMaxSize, WarningBlocks, WarningTime)
        );
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(NewCenterX);
        GETTER_SETTER(NewCenterZ);
        GETTER_SETTER(OldSize);
        GETTER_SETTER(NewSize);
        GETTER_SETTER(LerpTime);
        GETTER_SETTER(NewAbsoluteMaxSize);
        GETTER_SETTER(WarningBlocks);
        GETTER_SETTER(WarningTime);
    };
} //ProtocolCraft
#endif
