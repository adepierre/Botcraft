#if PROTOCOL_VERSION > 761 /* > 1.19.3 */
#pragma once

#include "protocolCraft/BasePacket.hpp"

namespace ProtocolCraft
{
    class ClientboundBundlePacket : public BasePacket<ClientboundBundlePacket>
    {
    public:
        static constexpr std::string_view packet_name = "Bundle";

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
#endif
