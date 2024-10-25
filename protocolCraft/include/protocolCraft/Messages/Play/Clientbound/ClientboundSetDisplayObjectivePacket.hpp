#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundSetDisplayObjectivePacket : public BaseMessage<ClientboundSetDisplayObjectivePacket>
    {
    public:
        static constexpr std::string_view packet_name = "Set Display Objective";

#if PROTOCOL_VERSION < 764 /* < 1.20.2 */
        SERIALIZED_FIELD(Slot, char);
#else
        SERIALIZED_FIELD(Slot, VarInt);
#endif
        SERIALIZED_FIELD(ObjectiveName, std::string);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
