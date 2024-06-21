#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ServerboundPlayerAbilitiesPacket : public BaseMessage<ServerboundPlayerAbilitiesPacket>
    {
    public:

        static constexpr std::string_view packet_name = "Player Abilities";

#if PROTOCOL_VERSION < 735 /* < 1.16 */
        DECLARE_FIELDS(
            (char,  float,       float),
            (Flags, FlyingSpeed, WalkingSpeed)
        );
#else
        DECLARE_FIELDS(
            (char),
            (Flags)
        );
#endif
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(Flags);
#if PROTOCOL_VERSION < 735 /* < 1.16 */
        GETTER_SETTER(FlyingSpeed);
        GETTER_SETTER(WalkingSpeed);
#endif
    };
} //ProtocolCraft
