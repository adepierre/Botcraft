#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundSetHealthPacket : public BaseMessage<ClientboundSetHealthPacket>
    {
    public:

        static constexpr std::string_view packet_name = "Set Health";

        DECLARE_FIELDS(
            (float,  VarInt, float),
            (Health, Food,   FoodSaturation)
        );
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(Health);
        GETTER_SETTER(Food);
        GETTER_SETTER(FoodSaturation);
    };
} //ProtocolCraft
