#if PROTOCOL_VERSION > 765 /* > 1.20.4 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"

#include <vector>

namespace ProtocolCraft
{
    class ClientboundDebugSamplePacket : public BaseMessage<ClientboundDebugSamplePacket>
    {
    public:
#if   PROTOCOL_VERSION == 766 /* 1.20.5/6 */ || PROTOCOL_VERSION == 767 /* 1.21 */
        static constexpr int packet_id = 0x1B;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Debug Sample";

        DECLARE_FIELDS_TYPES(std::vector<long long int>, VarInt);
        DECLARE_FIELDS_NAMES(Sample, DebugSampleType);
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(Sample);
        GETTER_SETTER(DebugSampleType);
    };
} //ProtocolCraft
#endif
