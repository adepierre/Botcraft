#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ServerboundPlayerInputPacket : public BaseMessage<ServerboundPlayerInputPacket>
    {
    public:

        static constexpr std::string_view packet_name = "Player Input";

        DECLARE_FIELDS(
            (float, float, unsigned char),
            (Xxa,   Zza,   Flags)
        );
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(Xxa);
        GETTER_SETTER(Zza);
        GETTER_SETTER(Flags);
    };
} //ProtocolCraft
