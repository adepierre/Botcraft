#if PROTOCOL_VERSION > 316 /* > 1.11.2 */
#pragma once

#include "protocolCraft/BasePacket.hpp"
#if PROTOCOL_VERSION < 777 /* < 26.3 */
#include "protocolCraft/Types/AdvancementHolder.hpp"
#else
#include "protocolCraft/Types/PositionedAdvancement.hpp"
#endif
#include "protocolCraft/Types/AdvancementProgress.hpp"
#include "protocolCraft/Types/Identifier.hpp"

#include <vector>

namespace ProtocolCraft
{
    class ClientboundUpdateAdvancementsPacket : public BasePacket<ClientboundUpdateAdvancementsPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Update Advancements";

        SERIALIZED_FIELD(ShouldReset, bool);
#if PROTOCOL_VERSION < 777 /* < 26.3 */
        SERIALIZED_FIELD(Added, std::vector<AdvancementHolder>);
#else
        SERIALIZED_FIELD(Added, std::vector<PositionedAdvancement>);
#endif
        SERIALIZED_FIELD(Removed, std::vector<Identifier>);
        SERIALIZED_FIELD(Progress, std::map<Identifier, AdvancementProgress>);
#if PROTOCOL_VERSION > 769 /* > 1.21.4 */
        SERIALIZED_FIELD(ShowAdvancements, bool);
#endif

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
#endif
