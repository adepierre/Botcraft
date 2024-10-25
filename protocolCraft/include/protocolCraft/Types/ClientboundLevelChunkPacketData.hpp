#if PROTOCOL_VERSION > 756 /* > 1.17.1 */
#pragma once

#include "protocolCraft/NetworkType.hpp"
#include "protocolCraft/Types/NBT/NBT.hpp"
#include "protocolCraft/Types/BlockEntityInfo.hpp"

namespace ProtocolCraft
{
    class ClientboundLevelChunkPacketData : public NetworkType
    {
        SERIALIZED_FIELD(Heightmaps, NBT::UnnamedValue);
        SERIALIZED_FIELD(Buffer, std::vector<unsigned char>);
        SERIALIZED_FIELD(BlockEntitiesData, std::vector<BlockEntityInfo>);

        DECLARE_READ_WRITE_SERIALIZE;
    };
}
#endif
