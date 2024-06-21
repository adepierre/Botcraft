#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/NetworkPosition.hpp"

namespace ProtocolCraft
{
    class ServerboundPlayerActionPacket : public BaseMessage<ServerboundPlayerActionPacket>
    {
    public:

        static constexpr std::string_view packet_name = "Player Action";

#if PROTOCOL_VERSION < 759 /* < 1.19 */
        DECLARE_FIELDS(
            (VarInt, NetworkPosition, char),
            (Action, Pos,             Direction)
        );
#else
        DECLARE_FIELDS(
            (VarInt, NetworkPosition, char,      VarInt),
            (Action, Pos,             Direction, Sequence)
        );
#endif
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(Action);
        GETTER_SETTER(Pos);
        GETTER_SETTER(Direction);
#if PROTOCOL_VERSION > 758 /* > 1.18.2 */
        GETTER_SETTER(Sequence);
#endif
    };
} //ProtocolCraft
