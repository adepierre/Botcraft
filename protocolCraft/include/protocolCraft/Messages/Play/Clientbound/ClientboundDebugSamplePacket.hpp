#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"

#include <vector>

namespace ProtocolCraft
{
    class ClientboundDebugSamplePacket : public BaseMessage<ClientboundDebugSamplePacket>
    {
    public:

        static constexpr std::string_view packet_name = "Debug Sample";

        DECLARE_FIELDS(
            (std::vector<long long int>, VarInt),
            (Sample, DebugSampleType)
        );
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(Sample);
        GETTER_SETTER(DebugSampleType);
    };
} //ProtocolCraft
#endif
