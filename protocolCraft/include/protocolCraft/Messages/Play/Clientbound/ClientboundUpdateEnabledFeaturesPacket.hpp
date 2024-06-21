#if PROTOCOL_VERSION > 760 /* > 1.19.2 */ && PROTOCOL_VERSION < 764 /* < 1.20.2 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/Identifier.hpp"

#include <vector>

namespace ProtocolCraft
{
    class ClientboundUpdateEnabledFeaturesPacket : public BaseMessage<ClientboundUpdateEnabledFeaturesPacket>
    {
    public:

        static constexpr std::string_view packet_name = "Update Enabled Features";

        DECLARE_FIELDS(
            (std::vector<Identifier>),
            (Features)
        );
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(Features);
    };
} //ProtocolCraft
#endif
