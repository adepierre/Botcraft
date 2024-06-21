#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundSetDisplayObjectivePacket : public BaseMessage<ClientboundSetDisplayObjectivePacket>
    {
    public:

        static constexpr std::string_view packet_name = "Set Display Objective";

#if PROTOCOL_VERSION < 764 /* < 1.20.2 */
        DECLARE_FIELDS(
            (char, std::string),
            (Slot, ObjectiveName)
        );
#else
        DECLARE_FIELDS(
            (VarInt, std::string),
            (Slot,   ObjectiveName)
        );
#endif
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(Slot);
        GETTER_SETTER(ObjectiveName);
    };
} //ProtocolCraft
