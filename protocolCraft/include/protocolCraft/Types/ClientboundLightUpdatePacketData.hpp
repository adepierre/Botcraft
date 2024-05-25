#if PROTOCOL_VERSION > 756 /* > 1.17.1 */
#pragma once

#include "protocolCraft/NetworkType.hpp"

namespace ProtocolCraft
{
    class ClientboundLightUpdatePacketData : public NetworkType
    {
#if PROTOCOL_VERSION < 763 /* < 1.20 */
        DECLARE_FIELDS_TYPES(bool,       std::vector<unsigned long long int>, std::vector<unsigned long long int>, std::vector<unsigned long long int>, std::vector<unsigned long long int>, std::vector<std::vector<char>>, std::vector<std::vector<char>>);
        DECLARE_FIELDS_NAMES(TrustEdges, SkyYMask,                            BlockYMask,                          EmptySkyYMask,                       EmptyBlockYMask,                     SkyUpdates,                     BlockUpdates);

#else
        DECLARE_FIELDS_TYPES(std::vector<unsigned long long int>, std::vector<unsigned long long int>, std::vector<unsigned long long int>, std::vector<unsigned long long int>, std::vector<std::vector<char>>, std::vector<std::vector<char>>);
        DECLARE_FIELDS_NAMES(SkyYMask,                            BlockYMask,                          EmptySkyYMask,                       EmptyBlockYMask,                     SkyUpdates,                     BlockUpdates);
#endif
        DECLARE_READ_WRITE_SERIALIZE;

#if PROTOCOL_VERSION < 763 /* < 1.20 */
        GETTER_SETTER(TrustEdges);
#endif
        GETTER_SETTER(SkyYMask);
        GETTER_SETTER(BlockYMask);
        GETTER_SETTER(EmptySkyYMask);
        GETTER_SETTER(EmptyBlockYMask);
        GETTER_SETTER(SkyUpdates);
        GETTER_SETTER(BlockUpdates);
    };
}
#endif
