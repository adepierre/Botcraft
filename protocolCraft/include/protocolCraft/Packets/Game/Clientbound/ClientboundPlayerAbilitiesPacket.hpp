#pragma once

#include "protocolCraft/BasePacket.hpp"

namespace ProtocolCraft
{
    class ClientboundPlayerAbilitiesPacket : public BasePacket<ClientboundPlayerAbilitiesPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Player Abilities";

        SERIALIZED_FIELD(Flags, char);
        SERIALIZED_FIELD(FlyingSpeed, float);
        SERIALIZED_FIELD(WalkingSpeed, float);

        DECLARE_READ_WRITE_SERIALIZE;
    };
}
