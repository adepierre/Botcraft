#if PROTOCOL_VERSION > 763 /* > 1.20.1 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ServerboundResourcePackConfigurationPacket : public BaseMessage<ServerboundResourcePackConfigurationPacket>
    {
    public:

        static constexpr std::string_view packet_name = "Resource Pack (Configuration)";

#if PROTOCOL_VERSION < 765 /* < 1.20.3 */
        DECLARE_FIELDS(
            (VarInt),
            (Action)
        );
#else
        DECLARE_FIELDS(
            (UUID, VarInt),
            (Uuid, Action)
        );
#endif
        DECLARE_READ_WRITE_SERIALIZE;

#if PROTOCOL_VERSION > 764 /* > 1.20.2 */
        GETTER_SETTER(Uuid);
#endif
        GETTER_SETTER(Action);
    };
} //ProtocolCraft
#endif
