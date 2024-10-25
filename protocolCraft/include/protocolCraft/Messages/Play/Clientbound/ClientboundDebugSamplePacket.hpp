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

        SERIALIZED_FIELD(Sample, std::vector<long long int>);
        SERIALIZED_FIELD(DebugSampleType, VarInt);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
#endif
