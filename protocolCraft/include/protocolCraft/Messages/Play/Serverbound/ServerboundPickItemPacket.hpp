#if PROTOCOL_VERSION > 385 /* > 1.12.2 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ServerboundPickItemPacket : public BaseMessage<ServerboundPickItemPacket>
    {
    public:

        static constexpr std::string_view packet_name = "Pick Item";

        DECLARE_FIELDS(
            (VarInt),
            (Slot)
        );
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(Slot);
    };
} //ProtocolCraft
#endif
