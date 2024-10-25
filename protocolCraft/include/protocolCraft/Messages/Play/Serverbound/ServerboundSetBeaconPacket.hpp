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
        SERIALIZED_FIELD(Primary, VarInt);
        SERIALIZED_FIELD(Secondary, VarInt);
#else
        SERIALIZED_FIELD(Primary, std::optional<VarInt>);
        SERIALIZED_FIELD(Secondary, std::optional<VarInt>);
#endif

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
#endif
