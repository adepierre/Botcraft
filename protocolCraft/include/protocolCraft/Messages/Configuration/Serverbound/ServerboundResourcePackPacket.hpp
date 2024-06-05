#if PROTOCOL_VERSION > 763 /* > 1.20.1 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ServerboundResourcePackConfigurationPacket : public BaseMessage<ServerboundResourcePackConfigurationPacket>
    {
    public:
#if   PROTOCOL_VERSION < 766 /* < 1.20.5 */
        static constexpr int packet_id = 0x05;
#elif PROTOCOL_VERSION == 766 /* 1.20.5/6 */
        static constexpr int packet_id = 0x06;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Resource Pack (Configuration)";

#if PROTOCOL_VERSION < 765 /* < 1.20.3 */
        DECLARE_FIELDS_TYPES(VarInt);
        DECLARE_FIELDS_NAMES(Action);
#else
        DECLARE_FIELDS_TYPES(UUID, VarInt);
        DECLARE_FIELDS_NAMES(Uuid, Action);
#endif
        DECLARE_READ_WRITE_SERIALIZE;

#if PROTOCOL_VERSION > 764 /* > 1.20.2 */
        GETTER_SETTER(Uuid);
#endif
        GETTER_SETTER(Action);
    };
} //ProtocolCraft
#endif
