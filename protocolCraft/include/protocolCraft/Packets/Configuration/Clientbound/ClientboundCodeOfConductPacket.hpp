#if PROTOCOL_VERSION > 772 /* > 1.21.8 */
#pragma once

#include "protocolCraft/BasePacket.hpp"

namespace ProtocolCraft
{
    class ClientboundCodeOfConductPacket : public BasePacket<ClientboundCodeOfConductPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Code Of Conduct";

        SERIALIZED_FIELD(CodeOfConduct, std::string);

        DECLARE_READ_WRITE_SERIALIZE;
    };
}
#endif
