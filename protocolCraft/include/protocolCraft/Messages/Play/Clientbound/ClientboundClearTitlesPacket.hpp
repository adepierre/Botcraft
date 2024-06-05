#if PROTOCOL_VERSION > 754 /* > 1.16.5 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundClearTitlesPacket : public BaseMessage<ClientboundClearTitlesPacket>
    {
    public:
#if   PROTOCOL_VERSION == 755 /* 1.17 */ || PROTOCOL_VERSION == 756 /* 1.17.1 */ ||  \
      PROTOCOL_VERSION == 757 /* 1.18/.1 */ || PROTOCOL_VERSION == 758 /* 1.18.2 */
        static constexpr int packet_id = 0x10;
#elif PROTOCOL_VERSION == 759 /* 1.19 */ || PROTOCOL_VERSION == 760 /* 1.19.1/2 */
        static constexpr int packet_id = 0x0D;
#elif PROTOCOL_VERSION == 761 /* 1.19.3 */
        static constexpr int packet_id = 0x0C;
#elif PROTOCOL_VERSION == 762 /* 1.19.4 */ || PROTOCOL_VERSION == 763 /* 1.20/.1 */
        static constexpr int packet_id = 0x0E;
#elif PROTOCOL_VERSION == 764 /* 1.20.2 */ || PROTOCOL_VERSION == 765 /* 1.20.3/4 */ ||  \
      PROTOCOL_VERSION == 766 /* 1.20.5/6 */
        static constexpr int packet_id = 0x0F;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Clear Titles";

        DECLARE_FIELDS_TYPES(bool);
        DECLARE_FIELDS_NAMES(ResetTimes);
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(ResetTimes);
    };
} //ProtocolCraft
#endif
