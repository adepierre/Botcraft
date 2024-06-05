#if PROTOCOL_VERSION < 755 /* < 1.17 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundContainerAckPacket : public BaseMessage<ClientboundContainerAckPacket>
    {
    public:
#if   PROTOCOL_VERSION == 340 /* 1.12.2 */
        static constexpr int packet_id = 0x11;
#elif PROTOCOL_VERSION == 393 /* 1.13 */ || PROTOCOL_VERSION == 401 /* 1.13.1 */ ||  \
      PROTOCOL_VERSION == 404 /* 1.13.2 */ || PROTOCOL_VERSION == 477 /* 1.14 */ ||  \
      PROTOCOL_VERSION == 480 /* 1.14.1 */ || PROTOCOL_VERSION == 485 /* 1.14.2 */ ||  \
      PROTOCOL_VERSION == 490 /* 1.14.3 */ || PROTOCOL_VERSION == 498 /* 1.14.4 */
        static constexpr int packet_id = 0x12;
#elif PROTOCOL_VERSION == 573 /* 1.15 */ || PROTOCOL_VERSION == 575 /* 1.15.1 */ ||  \
      PROTOCOL_VERSION == 578 /* 1.15.2 */
        static constexpr int packet_id = 0x13;
#elif PROTOCOL_VERSION == 735 /* 1.16 */ || PROTOCOL_VERSION == 736 /* 1.16.1 */
        static constexpr int packet_id = 0x12;
#elif PROTOCOL_VERSION == 751 /* 1.16.2 */ || PROTOCOL_VERSION == 753 /* 1.16.3 */ ||  \
      PROTOCOL_VERSION == 754 /* 1.16.4/5 */
        static constexpr int packet_id = 0x11;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Container Ack";

        DECLARE_FIELDS_TYPES(char,        short, bool);
        DECLARE_FIELDS_NAMES(ContainerId, Uid,   Accepted);
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(ContainerId);
        GETTER_SETTER(Uid);
        GETTER_SETTER(Accepted);
    };
} //ProtocolCraft
#endif
