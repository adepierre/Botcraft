#if PROTOCOL_VERSION > 47 /* > 1.8.9 */
#pragma once

#include "protocolCraft/BasePacket.hpp"

namespace ProtocolCraft
{
    class ClientboundSetPassengersPacket : public BasePacket<ClientboundSetPassengersPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Set Passengers";

        SERIALIZED_FIELD(Vehicle, VarInt);
        SERIALIZED_FIELD(Passengers, std::vector<VarInt>);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
#endif
