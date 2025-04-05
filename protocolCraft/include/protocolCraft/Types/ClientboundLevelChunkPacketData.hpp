#if PROTOCOL_VERSION > 756 /* > 1.17.1 */
#pragma once

#include "protocolCraft/NetworkType.hpp"
#include "protocolCraft/Types/NBT/NBT.hpp"
#include "protocolCraft/Types/BlockEntityInfo.hpp"

#if PROTOCOL_VERSION > 769 /* > 1.21.4 */
#include <map>
#endif

namespace ProtocolCraft
{
    class ClientboundLevelChunkPacketData : public NetworkType
    {
#if PROTOCOL_VERSION < 770 /* < 1.21.5 */
        SERIALIZED_FIELD(Heightmaps, NBT::UnnamedValue);
#else
        SERIALIZED_FIELD(Heightmaps, std::map<VarInt, std::vector<long long int>>);
#endif
        SERIALIZED_FIELD(Buffer, std::vector<unsigned char>);
        SERIALIZED_FIELD(BlockEntitiesData, std::vector<BlockEntityInfo>);

        DECLARE_READ_WRITE_SERIALIZE;
    };
}
#endif
