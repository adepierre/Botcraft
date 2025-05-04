#if PROTOCOL_VERSION > 760 /* > 1.19.2 */ && PROTOCOL_VERSION < 764 /* < 1.20.2 */
#pragma once

#include "protocolCraft/BasePacket.hpp"
#include "protocolCraft/Types/Identifier.hpp"

#include <vector>

namespace ProtocolCraft
{
    class ClientboundUpdateEnabledFeaturesPacket : public BasePacket<ClientboundUpdateEnabledFeaturesPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Update Enabled Features";

        SERIALIZED_FIELD(Features, std::vector<Identifier>);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
#endif
