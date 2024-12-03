#if PROTOCOL_VERSION > 385 /* > 1.12.2 */ && PROTOCOL_VERSION < 769 /* < 1.21.4 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ServerboundPickItemPacket : public BaseMessage<ServerboundPickItemPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Pick Item";

        SERIALIZED_FIELD(Slot, VarInt);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
#endif
