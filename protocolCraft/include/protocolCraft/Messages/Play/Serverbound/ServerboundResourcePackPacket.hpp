#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ServerboundResourcePackPacket : public BaseMessage<ServerboundResourcePackPacket>
    {
    public:

        static constexpr std::string_view packet_name = "Resource Pack";

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

        GETTER_SETTER(Action);
#if PROTOCOL_VERSION > 764 /* > 1.20.2 */
        GETTER_SETTER(Uuid);
#endif
    };
} //ProtocolCraft
