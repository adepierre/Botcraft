#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundSetExperiencePacket : public BaseMessage<ClientboundSetExperiencePacket>
    {
    public:
#if   PROTOCOL_VERSION == 340 /* 1.12.2 */
        static constexpr int packet_id = 0x40;
#elif PROTOCOL_VERSION == 393 /* 1.13 */ || PROTOCOL_VERSION == 401 /* 1.13.1 */ ||  \
      PROTOCOL_VERSION == 404 /* 1.13.2 */
        static constexpr int packet_id = 0x43;
#elif PROTOCOL_VERSION == 477 /* 1.14 */ || PROTOCOL_VERSION == 480 /* 1.14.1 */ ||  \
      PROTOCOL_VERSION == 485 /* 1.14.2 */ || PROTOCOL_VERSION == 490 /* 1.14.3 */ ||  \
      PROTOCOL_VERSION == 498 /* 1.14.4 */
        static constexpr int packet_id = 0x47;
#elif PROTOCOL_VERSION == 573 /* 1.15 */ || PROTOCOL_VERSION == 575 /* 1.15.1 */ ||  \
      PROTOCOL_VERSION == 578 /* 1.15.2 */ || PROTOCOL_VERSION == 735 /* 1.16 */ ||  \
      PROTOCOL_VERSION == 736 /* 1.16.1 */ || PROTOCOL_VERSION == 751 /* 1.16.2 */ ||  \
      PROTOCOL_VERSION == 753 /* 1.16.3 */ || PROTOCOL_VERSION == 754 /* 1.16.4/5 */
        static constexpr int packet_id = 0x48;
#elif PROTOCOL_VERSION == 755 /* 1.17 */ || PROTOCOL_VERSION == 756 /* 1.17.1 */ ||  \
      PROTOCOL_VERSION == 757 /* 1.18/.1 */ || PROTOCOL_VERSION == 758 /* 1.18.2 */ ||  \
      PROTOCOL_VERSION == 759 /* 1.19 */
        static constexpr int packet_id = 0x51;
#elif PROTOCOL_VERSION == 760 /* 1.19.1/2 */
        static constexpr int packet_id = 0x54;
#elif PROTOCOL_VERSION == 761 /* 1.19.3 */
        static constexpr int packet_id = 0x52;
#elif PROTOCOL_VERSION == 762 /* 1.19.4 */ || PROTOCOL_VERSION == 763 /* 1.20/.1 */
        static constexpr int packet_id = 0x56;
#elif PROTOCOL_VERSION == 764 /* 1.20.2 */
        static constexpr int packet_id = 0x58;
#elif PROTOCOL_VERSION == 765 /* 1.20.3/4 */
        static constexpr int packet_id = 0x5A;
#elif PROTOCOL_VERSION == 766 /* 1.20.5/6 */
        static constexpr int packet_id = 0x5C;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Set Experience";

        DECLARE_FIELDS_TYPES(float,              VarInt,          VarInt);
        DECLARE_FIELDS_NAMES(ExperienceProgress, ExperienceLevel, TotalExperience);
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(ExperienceProgress);
        GETTER_SETTER(ExperienceLevel);
        GETTER_SETTER(TotalExperience);
    };
} //ProtocolCraft
