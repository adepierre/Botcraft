#if PROTOCOL_VERSION > 763 /* > 1.20.1 */
#pragma once

#include "protocolCraft/BasePacket.hpp"

namespace ProtocolCraft
{
    class ServerboundKeepAliveConfigurationPacket : public BasePacket<ServerboundKeepAliveConfigurationPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Keep Alive (Configuration)";

        SERIALIZED_FIELD(Id_, long long int);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
#endif
