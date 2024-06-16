#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/KnownPack.hpp"

#include <vector>

namespace ProtocolCraft
{
    class ClientboundSelectKnownPacksPacket : public BaseMessage<ClientboundSelectKnownPacksPacket>
    {
    public:
        static constexpr int packet_id = 0x0E;
        static constexpr std::string_view packet_name = "Select Known Packs";

        DECLARE_FIELDS(
            (std::vector<KnownPack>),
            (KnownPacks)
        );
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(KnownPacks);
    };
} // ProtocolCraft
#endif
