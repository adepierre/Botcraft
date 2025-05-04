#pragma once

#include <map>

#include "protocolCraft/BasePacket.hpp"
#include "protocolCraft/Types/Advancement.hpp"
#include "protocolCraft/Types/AdvancementProgress.hpp"
#include "protocolCraft/Types/Identifier.hpp"

namespace ProtocolCraft
{
    class ClientboundUpdateAdvancementsPacket : public BasePacket<ClientboundUpdateAdvancementsPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Update Advancements";

        SERIALIZED_FIELD(Reset, bool);
        SERIALIZED_FIELD(Added, std::map<Identifier, Advancement>);
        SERIALIZED_FIELD(Removed, std::vector<Identifier>);
        SERIALIZED_FIELD(Progress, std::map<Identifier, AdvancementProgress>);
#if PROTOCOL_VERSION > 769 /* > 1.21.4 */
        SERIALIZED_FIELD(ShowAdvancements, bool);
#endif

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
