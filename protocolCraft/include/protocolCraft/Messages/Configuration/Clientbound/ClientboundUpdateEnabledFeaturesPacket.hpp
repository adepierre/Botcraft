#if PROTOCOL_VERSION > 763 /* > 1.20.1 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"

#include <vector>
#include <string>

namespace ProtocolCraft
{
    class ClientboundUpdateEnabledFeaturesPacket : public BaseMessage<ClientboundUpdateEnabledFeaturesPacket>
    {
    public:

        static constexpr std::string_view packet_name = "Update Enabled Features";

        DECLARE_FIELDS(
            (std::vector<std::string>),
            (Features)
        );
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(Features);
    };
} //ProtocolCraft
#endif
