#if PROTOCOL_VERSION > 761 /* > 1.19.3 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundBundlePacket : public BaseMessage<ClientboundBundlePacket>
    {
    public:
        static constexpr std::string_view packet_name = "Bundle";

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
#endif
