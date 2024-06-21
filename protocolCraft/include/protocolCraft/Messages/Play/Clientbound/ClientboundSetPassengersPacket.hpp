#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundSetPassengersPacket : public BaseMessage<ClientboundSetPassengersPacket>
    {
    public:

        static constexpr std::string_view packet_name = "Set Passengers";

        DECLARE_FIELDS(
            (VarInt, std::vector<VarInt>),
            (Vehicle, Passengers)
        );
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(Vehicle);
        GETTER_SETTER(Passengers);
    };
} //ProtocolCraft
