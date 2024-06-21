#pragma once

#include <map>

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/Advancement.hpp"
#include "protocolCraft/Types/AdvancementProgress.hpp"
#include "protocolCraft/Types/Identifier.hpp"

namespace ProtocolCraft
{
    class ClientboundUpdateAdvancementsPacket : public BaseMessage<ClientboundUpdateAdvancementsPacket>
    {
    public:

        static constexpr std::string_view packet_name = "Update Advancements";

        DECLARE_FIELDS(
            (bool,  std::map<Identifier, Advancement>, std::vector<Identifier>, std::map<Identifier, AdvancementProgress>),
            (Reset, Added,                             Removed,                 Progress)
        );
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(Reset);
        GETTER_SETTER(Added);
        GETTER_SETTER(Removed);
        GETTER_SETTER(Progress);
    };
} //ProtocolCraft
