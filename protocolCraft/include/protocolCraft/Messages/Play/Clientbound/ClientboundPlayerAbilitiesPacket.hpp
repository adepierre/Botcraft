#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundPlayerAbilitiesPacket : public BaseMessage<ClientboundPlayerAbilitiesPacket>
    {
    public:

        static constexpr std::string_view packet_name = "Player Abilities";

        DECLARE_FIELDS(
            (char, float, float),
            (Flags, FlyingSpeed, WalkingSpeed)
        );
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(Flags);
        GETTER_SETTER(FlyingSpeed);
        GETTER_SETTER(WalkingSpeed);
    };
}
