#pragma once

#include "protocolCraft/BasePacket.hpp"

namespace ProtocolCraft
{
    class ClientboundSetHealthPacket : public BasePacket<ClientboundSetHealthPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Set Health";

        SERIALIZED_FIELD(Health, float);
        SERIALIZED_FIELD(Food, VarInt);
        SERIALIZED_FIELD(FoodSaturation, float);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
