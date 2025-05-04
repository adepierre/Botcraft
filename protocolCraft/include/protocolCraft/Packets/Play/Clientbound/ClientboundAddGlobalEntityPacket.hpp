#if PROTOCOL_VERSION < 721 /* < 1.16 */
#pragma once

#include "protocolCraft/BasePacket.hpp"

namespace ProtocolCraft
{
    class ClientboundAddGlobalEntityPacket : public BasePacket<ClientboundAddGlobalEntityPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Add Global Entity";

        SERIALIZED_FIELD(EntityId, VarInt);
        SERIALIZED_FIELD(Type, char);
        SERIALIZED_FIELD(X, double);
        SERIALIZED_FIELD(Y, double);
        SERIALIZED_FIELD(Z, double);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
#endif
