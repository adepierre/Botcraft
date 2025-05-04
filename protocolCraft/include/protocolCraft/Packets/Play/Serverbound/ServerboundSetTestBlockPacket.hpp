#if PROTOCOL_VERSION > 769 /* > 1.21.4 */
#pragma once

#include "protocolCraft/BasePacket.hpp"
#include "protocolCraft/Types/NetworkPosition.hpp"

namespace ProtocolCraft
{
    class ServerboundSetTestBlockPacket : public BasePacket<ServerboundSetTestBlockPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Set Test Block";

        SERIALIZED_FIELD(Position, NetworkPosition);
        SERIALIZED_FIELD(Mode, VarInt);
        SERIALIZED_FIELD(Message, std::string);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
#endif
