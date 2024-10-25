#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ServerboundPlayerAbilitiesPacket : public BaseMessage<ServerboundPlayerAbilitiesPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Player Abilities";

        SERIALIZED_FIELD(Flags, char);
#if PROTOCOL_VERSION < 735 /* < 1.16 */
        SERIALIZED_FIELD(FlyingSpeed, float);
        SERIALIZED_FIELD(WalkingSpeed, float);
#endif

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
