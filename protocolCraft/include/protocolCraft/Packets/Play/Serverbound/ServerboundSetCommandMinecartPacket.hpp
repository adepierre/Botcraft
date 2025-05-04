#if PROTOCOL_VERSION > 385 /* > 1.12.2 */
#pragma once

#include "protocolCraft/BasePacket.hpp"

namespace ProtocolCraft
{
    class ServerboundSetCommandMinecartPacket : public BasePacket<ServerboundSetCommandMinecartPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Set Command Minecart";

        SERIALIZED_FIELD(Entity, VarInt);
        SERIALIZED_FIELD(Command, std::string);
        SERIALIZED_FIELD(TrackOutput, bool);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
#endif
