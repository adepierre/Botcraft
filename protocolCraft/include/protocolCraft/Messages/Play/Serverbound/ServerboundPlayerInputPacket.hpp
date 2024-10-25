#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ServerboundPlayerInputPacket : public BaseMessage<ServerboundPlayerInputPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Player Input";

        SERIALIZED_FIELD(Xxa, float);
        SERIALIZED_FIELD(Zza, float);
        SERIALIZED_FIELD(Flags, unsigned char);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
