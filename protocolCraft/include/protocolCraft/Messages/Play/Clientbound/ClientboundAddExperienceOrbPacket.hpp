#if PROTOCOL_VERSION < 770 /* < 1.21.5 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundAddExperienceOrbPacket : public BaseMessage<ClientboundAddExperienceOrbPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Add Experience Orb";

        SERIALIZED_FIELD(EntityId, VarInt);
        SERIALIZED_FIELD(X, double);
        SERIALIZED_FIELD(Y, double);
        SERIALIZED_FIELD(Z, double);
        SERIALIZED_FIELD(Value, short);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
#endif
