#if PROTOCOL_VERSION < 768 /* < 1.21.2 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundSetCarriedItemPacket : public BaseMessage<ClientboundSetCarriedItemPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Set Carried Item";

        SERIALIZED_FIELD(Slot, char);

        DECLARE_READ_WRITE_SERIALIZE;
    };
}
#endif
