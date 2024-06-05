#if PROTOCOL_VERSION > 754 /* > 1.16.5 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/Chat/Chat.hpp"

namespace ProtocolCraft
{
    class ClientboundPlayerCombatKillPacket : public BaseMessage<ClientboundPlayerCombatKillPacket>
    {
    public:
#if   PROTOCOL_VERSION == 755 /* 1.17 */ || PROTOCOL_VERSION == 756 /* 1.17.1 */ ||  \
      PROTOCOL_VERSION == 757 /* 1.18/.1 */ || PROTOCOL_VERSION == 758 /* 1.18.2 */
        static constexpr int packet_id = 0x35;
#elif PROTOCOL_VERSION == 759 /* 1.19 */
        static constexpr int packet_id = 0x33;
#elif PROTOCOL_VERSION == 760 /* 1.19.1/2 */
        static constexpr int packet_id = 0x36;
#elif PROTOCOL_VERSION == 761 /* 1.19.3 */
        static constexpr int packet_id = 0x34;
#elif PROTOCOL_VERSION == 762 /* 1.19.4 */ || PROTOCOL_VERSION == 763 /* 1.20/.1 */
        static constexpr int packet_id = 0x38;
#elif PROTOCOL_VERSION == 764 /* 1.20.2 */ || PROTOCOL_VERSION == 765 /* 1.20.3/4 */
        static constexpr int packet_id = 0x3A;
#elif PROTOCOL_VERSION == 766 /* 1.20.5/6 */
        static constexpr int packet_id = 0x3C;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Player Combat Kill";

#if PROTOCOL_VERSION < 763 /* < 1.20 */
        DECLARE_FIELDS_TYPES(VarInt,   int,      Chat);
        DECLARE_FIELDS_NAMES(PlayerId, KillerId, Message);
#else
        DECLARE_FIELDS_TYPES(VarInt,   Chat);
        DECLARE_FIELDS_NAMES(PlayerId, Message);
#endif
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(PlayerId);
#if PROTOCOL_VERSION < 763 /* < 1.20 */
        GETTER_SETTER(KillerId);
#endif
        GETTER_SETTER(Message);
    };
} //ProtocolCraft
#endif
