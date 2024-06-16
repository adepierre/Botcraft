#if PROTOCOL_VERSION > 761 /* > 1.19.3 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundHurtAnimationPacket : public BaseMessage<ClientboundHurtAnimationPacket>
    {
    public:
#if   PROTOCOL_VERSION == 762 /* 1.19.4 */ || PROTOCOL_VERSION == 763 /* 1.20/.1 */
        static constexpr int packet_id = 0x21;
#elif PROTOCOL_VERSION == 764 /* 1.20.2 */ || PROTOCOL_VERSION == 765 /* 1.20.3/4 */
        static constexpr int packet_id = 0x22;
#elif PROTOCOL_VERSION == 766 /* 1.20.5/6 */ || PROTOCOL_VERSION == 767 /* 1.21 */
        static constexpr int packet_id = 0x24;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Hurt Animation";

        DECLARE_FIELDS_TYPES(VarInt, float);
        DECLARE_FIELDS_NAMES(Id_, Yaw);
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(Id_);
        GETTER_SETTER(Yaw);
    };
} //ProtocolCraft
#endif
