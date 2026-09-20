#if PROTOCOL_VERSION > 776 /* > 26.2 */
#pragma once
#include "protocolCraft/BasePacket.hpp"

#include "protocolCraft/Types/Identifier.hpp"

#include <vector>

namespace ProtocolCraft
{
    class ClientboundPostEffectsPacket : public BasePacket<ClientboundPostEffectsPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Post Effects";

        SERIALIZED_FIELD(PostEffects, std::vector<Identifier>);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
#endif
