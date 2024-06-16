#if PROTOCOL_VERSION > 754 /* > 1.16.5 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundInitializeBorderPacket : public BaseMessage<ClientboundInitializeBorderPacket>
    {
    public:
#if   PROTOCOL_VERSION == 755 /* 1.17 */ || PROTOCOL_VERSION == 756 /* 1.17.1 */ ||  \
      PROTOCOL_VERSION == 757 /* 1.18/.1 */ || PROTOCOL_VERSION == 758 /* 1.18.2 */
        static constexpr int packet_id = 0x20;
#elif PROTOCOL_VERSION == 759 /* 1.19 */
        static constexpr int packet_id = 0x1D;
#elif PROTOCOL_VERSION == 760 /* 1.19.1/2 */
        static constexpr int packet_id = 0x1F;
#elif PROTOCOL_VERSION == 761 /* 1.19.3 */
        static constexpr int packet_id = 0x1E;
#elif PROTOCOL_VERSION == 762 /* 1.19.4 */ || PROTOCOL_VERSION == 763 /* 1.20/.1 */
        static constexpr int packet_id = 0x22;
#elif PROTOCOL_VERSION == 764 /* 1.20.2 */ || PROTOCOL_VERSION == 765 /* 1.20.3/4 */
        static constexpr int packet_id = 0x23;
#elif PROTOCOL_VERSION == 766 /* 1.20.5/6 */ || PROTOCOL_VERSION == 767 /* 1.21 */
        static constexpr int packet_id = 0x25;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Initialize Border";

        DECLARE_FIELDS_TYPES(double,     double,     double,  double,  VarLong,  VarInt,             VarInt,        VarInt);
        DECLARE_FIELDS_NAMES(NewCenterX, NewCenterZ, OldSize, NewSize, LerpTime, NewAbsoluteMaxSize, WarningBlocks, WarningTime);
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
