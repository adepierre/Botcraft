#if PROTOCOL_VERSION > 344 /* > 1.12.2 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/CommandNode/CommandNode.hpp"

namespace ProtocolCraft
{
    class ClientboundCommandsPacket : public BaseMessage<ClientboundCommandsPacket>
    {
    public:
#if   PROTOCOL_VERSION == 393 /* 1.13 */ || PROTOCOL_VERSION == 401 /* 1.13.1 */ ||  \
      PROTOCOL_VERSION == 404 /* 1.13.2 */ || PROTOCOL_VERSION == 477 /* 1.14 */ ||  \
      PROTOCOL_VERSION == 480 /* 1.14.1 */ || PROTOCOL_VERSION == 485 /* 1.14.2 */ ||  \
      PROTOCOL_VERSION == 490 /* 1.14.3 */ || PROTOCOL_VERSION == 498 /* 1.14.4 */
        static constexpr int packet_id = 0x11;
#elif PROTOCOL_VERSION == 573 /* 1.15 */ || PROTOCOL_VERSION == 575 /* 1.15.1 */ ||  \
      PROTOCOL_VERSION == 578 /* 1.15.2 */
        static constexpr int packet_id = 0x12;
#elif PROTOCOL_VERSION == 735 /* 1.16 */ || PROTOCOL_VERSION == 736 /* 1.16.1 */
        static constexpr int packet_id = 0x11;
#elif PROTOCOL_VERSION == 751 /* 1.16.2 */ || PROTOCOL_VERSION == 753 /* 1.16.3 */ ||  \
      PROTOCOL_VERSION == 754 /* 1.16.4/5 */
        static constexpr int packet_id = 0x10;
#elif PROTOCOL_VERSION == 755 /* 1.17 */ || PROTOCOL_VERSION == 756 /* 1.17.1 */ ||  \
      PROTOCOL_VERSION == 757 /* 1.18/.1 */ || PROTOCOL_VERSION == 758 /* 1.18.2 */
        static constexpr int packet_id = 0x12;
#elif PROTOCOL_VERSION == 759 /* 1.19 */ || PROTOCOL_VERSION == 760 /* 1.19.1/2 */
        static constexpr int packet_id = 0x0F;
#elif PROTOCOL_VERSION == 761 /* 1.19.3 */
        static constexpr int packet_id = 0x0E;
#elif PROTOCOL_VERSION == 762 /* 1.19.4 */ || PROTOCOL_VERSION == 763 /* 1.20/.1 */
        static constexpr int packet_id = 0x10;
#elif PROTOCOL_VERSION == 764 /* 1.20.2 */ || PROTOCOL_VERSION == 765 /* 1.20.3/4 */ ||  \
      PROTOCOL_VERSION == 766 /* 1.20.5/6 */
        static constexpr int packet_id = 0x11;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Commands";

        DECLARE_FIELDS_TYPES(std::vector<CommandNode>, VarInt);
        DECLARE_FIELDS_NAMES(Nodes,                    RootIndex);
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(Nodes);
        GETTER_SETTER(RootIndex);
    };
} //ProtocolCraft
#endif
