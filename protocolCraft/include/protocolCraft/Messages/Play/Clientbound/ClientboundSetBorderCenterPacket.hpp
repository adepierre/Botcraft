#if PROTOCOL_VERSION > 754 /* > 1.16.5 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundSetBorderCenterPacket : public BaseMessage<ClientboundSetBorderCenterPacket>
    {
    public:
#if   PROTOCOL_VERSION == 755 /* 1.17 */ || PROTOCOL_VERSION == 756 /* 1.17.1 */ ||  \
      PROTOCOL_VERSION == 757 /* 1.18/.1 */ || PROTOCOL_VERSION == 758 /* 1.18.2 */
        static constexpr int packet_id = 0x42;
#elif PROTOCOL_VERSION == 759 /* 1.19 */
        static constexpr int packet_id = 0x41;
#elif PROTOCOL_VERSION == 760 /* 1.19.1/2 */
        static constexpr int packet_id = 0x44;
#elif PROTOCOL_VERSION == 761 /* 1.19.3 */
        static constexpr int packet_id = 0x43;
#elif PROTOCOL_VERSION == 762 /* 1.19.4 */ || PROTOCOL_VERSION == 763 /* 1.20/.1 */
        static constexpr int packet_id = 0x47;
#elif PROTOCOL_VERSION == 764 /* 1.20.2 */
        static constexpr int packet_id = 0x49;
#elif PROTOCOL_VERSION == 765 /* 1.20.3/4 */
        static constexpr int packet_id = 0x4B;
#elif PROTOCOL_VERSION == 766 /* 1.20.5/6 */
        static constexpr int packet_id = 0x4D;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Set Border Center";

        DECLARE_FIELDS_TYPES(double,     double);
        DECLARE_FIELDS_NAMES(NewCenterX, NewCenterZ);
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(NewCenterX);
        GETTER_SETTER(NewCenterZ);
    };
} //ProtocolCraft
#endif
