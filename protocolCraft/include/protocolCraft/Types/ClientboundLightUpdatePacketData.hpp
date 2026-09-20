#if PROTOCOL_VERSION > 756 /* > 1.17.1 */
#pragma once

#include "protocolCraft/NetworkType.hpp"

namespace ProtocolCraft
{
    class ClientboundLightUpdatePacketData : public NetworkType
    {
#if PROTOCOL_VERSION < 763 /* < 1.20 */
        SERIALIZED_FIELD(TrustEdges, bool);
#endif
#if PROTOCOL_VERSION < 777 /* < 26.3 */
        SERIALIZED_FIELD(SkyYMask, std::vector<unsigned long long int>);
        SERIALIZED_FIELD(BlockYMask, std::vector<unsigned long long int>);
        SERIALIZED_FIELD(EmptySkyYMask, std::vector<unsigned long long int>);
        SERIALIZED_FIELD(EmptyBlockYMask, std::vector<unsigned long long int>);
#else
        SERIALIZED_FIELD(SkyYMask, std::vector<unsigned char>);
        SERIALIZED_FIELD(BlockYMask, std::vector<unsigned char>);
        SERIALIZED_FIELD(EmptySkyYMask, std::vector<unsigned char>);
        SERIALIZED_FIELD(EmptyBlockYMask, std::vector<unsigned char>);
#endif
        SERIALIZED_FIELD(SkyUpdates, std::vector<std::vector<char>>);
        SERIALIZED_FIELD(BlockUpdates, std::vector<std::vector<char>>);

        DECLARE_READ_WRITE_SERIALIZE;
    };
}
#endif
