#if PROTOCOL_VERSION > 756 /* > 1.17.1 */
#pragma once

#include "protocolCraft/NetworkType.hpp"
#include "protocolCraft/Types/NBT/NBT.hpp"
#include "protocolCraft/Types/BlockEntityInfo.hpp"

namespace ProtocolCraft
{
    class ClientboundLevelChunkPacketData : public NetworkType
    {
        DECLARE_FIELDS(
            (NBT::UnnamedValue, std::vector<unsigned char>, std::vector<BlockEntityInfo>),
            (Heightmaps,        Buffer,                     BlockEntitiesData)
        );
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(Heightmaps);
        GETTER_SETTER(Buffer);
        GETTER_SETTER(BlockEntitiesData);
    };
}
#endif
