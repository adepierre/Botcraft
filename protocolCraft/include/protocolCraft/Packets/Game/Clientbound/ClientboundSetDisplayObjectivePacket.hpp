#pragma once

#include "protocolCraft/BasePacket.hpp"

namespace ProtocolCraft
{
    class ClientboundSetDisplayObjectivePacket : public BasePacket<ClientboundSetDisplayObjectivePacket>
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
