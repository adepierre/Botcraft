#if PROTOCOL_VERSION < 770 /* < 1.21.5 */
#pragma once

#include "protocolCraft/BasePacket.hpp"

namespace ProtocolCraft
{
    class ClientboundAddExperienceOrbPacket : public BasePacket<ClientboundAddExperienceOrbPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Add Experience Orb";

        SERIALIZED_FIELD(EntityId, VarInt);
#if PROTOCOL_VERSION < 107 /* < 1.9 */
        SERIALIZED_FIELD(X, int);
        SERIALIZED_FIELD(Y, int);
        SERIALIZED_FIELD(Z, int);
#else
        SERIALIZED_FIELD(X, double);
        SERIALIZED_FIELD(Y, double);
        SERIALIZED_FIELD(Z, double);
#endif
        SERIALIZED_FIELD(Value, short);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
#endif
