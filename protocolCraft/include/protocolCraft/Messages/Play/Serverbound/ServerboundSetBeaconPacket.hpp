#if PROTOCOL_VERSION > 385 /* > 1.12.2 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ServerboundSetBeaconPacket : public BaseMessage<ServerboundSetBeaconPacket>
    {
    public:

        static constexpr std::string_view packet_name = "Set Beacon";

#if PROTOCOL_VERSION < 759 /* < 1.19 */
        DECLARE_FIELDS(
            (VarInt,  VarInt),
            (Primary, Secondary)
        );
#else
        DECLARE_FIELDS(
            (std::optional<VarInt>,  std::optional<VarInt>),
            (Primary,                Secondary)
        );
#endif
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(Primary);
        GETTER_SETTER(Secondary);
    };
} //ProtocolCraft
#endif
