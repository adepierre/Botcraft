#if PROTOCOL_VERSION > 385 /* > 1.12.2 */
#pragma once

#include "protocolCraft/BasePacket.hpp"
#include "protocolCraft/Types/NetworkPosition.hpp"

namespace ProtocolCraft
{
    class ServerboundSetCommandBlockPacket : public BasePacket<ServerboundSetCommandBlockPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Set Command Block";

        SERIALIZED_FIELD(Pos, NetworkPosition);
        SERIALIZED_FIELD(Command, std::string);
        SERIALIZED_FIELD(Mode, VarInt);
        SERIALIZED_FIELD(Flags, char);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
#endif
