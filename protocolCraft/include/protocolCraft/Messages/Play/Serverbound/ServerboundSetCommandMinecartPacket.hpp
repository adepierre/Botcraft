#if PROTOCOL_VERSION > 385 /* > 1.12.2 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ServerboundSetCommandMinecartPacket : public BaseMessage<ServerboundSetCommandMinecartPacket>
    {
    public:

        static constexpr std::string_view packet_name = "Set Command Minecart";

        DECLARE_FIELDS(
            (VarInt, std::string, bool),
            (Entity, Command,     TrackOutput)
        );
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(Entity);
        GETTER_SETTER(Command);
        GETTER_SETTER(TrackOutput);
    };
} //ProtocolCraft
#endif
