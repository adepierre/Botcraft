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
        static constexpr std::string_view packet_name = "Select Known Packs";

        SERIALIZED_FIELD(KnownPacks, std::vector<KnownPack>);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} // ProtocolCraft
#endif
