#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundSetExperiencePacket : public BaseMessage<ClientboundSetExperiencePacket>
    {
    public:
        static constexpr std::string_view packet_name = "Set Experience";

        SERIALIZED_FIELD(ExperienceProgress, float);
        SERIALIZED_FIELD(ExperienceLevel, VarInt);
        SERIALIZED_FIELD(TotalExperience, VarInt);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
