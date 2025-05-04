#pragma once

#include "protocolCraft/BasePacket.hpp"

namespace ProtocolCraft
{
    class ClientboundSetExperiencePacket : public BasePacket<ClientboundSetExperiencePacket>
    {
    public:
        static constexpr std::string_view packet_name = "Set Experience";

        SERIALIZED_FIELD(ExperienceProgress, float);
        SERIALIZED_FIELD(ExperienceLevel, VarInt);
        SERIALIZED_FIELD(TotalExperience, VarInt);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
