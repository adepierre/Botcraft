#if PROTOCOL_VERSION > 385 /* > 1.12.2 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/NetworkPosition.hpp"

namespace ProtocolCraft
{
    class ServerboundSetCommandBlockPacket : public BaseMessage<ServerboundSetCommandBlockPacket>
    {
    public:

        static constexpr std::string_view packet_name = "Set Command Block";

        DECLARE_FIELDS(
            (NetworkPosition, std::string, VarInt, char),
            (Pos,             Command,     Mode,   Flags)
        );
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(Pos);
        GETTER_SETTER(Command);
        GETTER_SETTER(Mode);
        GETTER_SETTER(Flags);
    };
} //ProtocolCraft
#endif
