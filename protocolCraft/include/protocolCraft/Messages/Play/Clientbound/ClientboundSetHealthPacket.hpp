#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundSetHealthPacket : public BaseMessage<ClientboundSetHealthPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Set Health";

        SERIALIZED_FIELD(Health, float);
        SERIALIZED_FIELD(Food, VarInt);
        SERIALIZED_FIELD(FoodSaturation, float);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
