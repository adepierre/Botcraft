#if PROTOCOL_VERSION > 763 /* > 1.20.1 */
#pragma once

#include "protocolCraft/BasePacket.hpp"

#include <vector>
#include <string>

namespace ProtocolCraft
{
    class ClientboundUpdateEnabledFeaturesPacket : public BasePacket<ClientboundUpdateEnabledFeaturesPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Update Enabled Features";

        SERIALIZED_FIELD(Features, std::vector<std::string>);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
#endif
