#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/NetworkPosition.hpp"

namespace ProtocolCraft
{
    class ServerboundPlayerActionPacket : public BaseMessage<ServerboundPlayerActionPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Player Action";

        SERIALIZED_FIELD(Action, VarInt);
        SERIALIZED_FIELD(Pos, NetworkPosition);
        SERIALIZED_FIELD(Direction, char);
#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
        SERIALIZED_FIELD(Sequence, VarInt);
#endif

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
