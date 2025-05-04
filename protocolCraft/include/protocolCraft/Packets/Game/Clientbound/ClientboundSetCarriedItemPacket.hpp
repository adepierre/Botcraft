#if PROTOCOL_VERSION < 768 /* < 1.21.2 */
#pragma once

#include "protocolCraft/BasePacket.hpp"

namespace ProtocolCraft
{
    class ClientboundSetCarriedItemPacket : public BasePacket<ClientboundSetCarriedItemPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Set Carried Item";

        SERIALIZED_FIELD(Slot, char);

        DECLARE_READ_WRITE_SERIALIZE;
    };
}
#endif
