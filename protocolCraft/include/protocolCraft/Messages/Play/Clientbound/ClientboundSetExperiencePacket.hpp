#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundSetExperiencePacket : public BaseMessage<ClientboundSetExperiencePacket>
    {
    public:

        static constexpr std::string_view packet_name = "Set Experience";

        DECLARE_FIELDS(
            (float,              VarInt,          VarInt),
            (ExperienceProgress, ExperienceLevel, TotalExperience)
        );
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(ExperienceProgress);
        GETTER_SETTER(ExperienceLevel);
        GETTER_SETTER(TotalExperience);
    };
} //ProtocolCraft
