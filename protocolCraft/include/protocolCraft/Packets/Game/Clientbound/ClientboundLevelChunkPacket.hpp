#if PROTOCOL_VERSION < 757 /* < 1.18 */
#pragma once

#include "protocolCraft/BasePacket.hpp"
#include "protocolCraft/Types/NBT/NBT.hpp"

namespace ProtocolCraft
{

    class ClientboundLevelChunkPacket : public BasePacket<ClientboundLevelChunkPacket>
    {
    public:
        static constexpr std::string_view packet_name = "Level Chunk";

#if PROTOCOL_VERSION > 551 /* > 1.14.4 */ && PROTOCOL_VERSION < 755 /* < 1.17 */
        DEFINE_CONDITION(HasFullChunk, GetFullChunk());
#endif

        SERIALIZED_FIELD(X, int);
        SERIALIZED_FIELD(Z, int);
#if PROTOCOL_VERSION < 477 /* < 1.14 */
        SERIALIZED_FIELD(FullChunk, bool);
        SERIALIZED_FIELD(AvailableSections, VarInt);
#elif PROTOCOL_VERSION < 573 /* < 1.15 */
        SERIALIZED_FIELD(FullChunk, bool);
        SERIALIZED_FIELD(AvailableSections, VarInt);
        SERIALIZED_FIELD(Heightmaps, NBT::UnnamedValue);
#elif PROTOCOL_VERSION < 735 /* < 1.16 */
        SERIALIZED_FIELD(FullChunk, bool);
        SERIALIZED_FIELD(AvailableSections, VarInt);
        SERIALIZED_FIELD(Heightmaps, NBT::UnnamedValue);
        SERIALIZED_FIELD(Biomes, Internal::Conditioned<std::array<int, 1024>, &THIS::HasFullChunk>);
#elif PROTOCOL_VERSION < 751 /* < 1.16.2 */
        SERIALIZED_FIELD(FullChunk, bool);
        SERIALIZED_FIELD(IgnoreOldData, bool);
        SERIALIZED_FIELD(AvailableSections, VarInt);
        SERIALIZED_FIELD(Heightmaps, NBT::UnnamedValue);
        SERIALIZED_FIELD(Biomes, Internal::Conditioned<std::array<int, 1024>, &THIS::HasFullChunk>);
#elif PROTOCOL_VERSION < 755 /* < 1.17 */
        SERIALIZED_FIELD(FullChunk, bool);
        SERIALIZED_FIELD(AvailableSections, VarInt);
        SERIALIZED_FIELD(Heightmaps, NBT::UnnamedValue);
        SERIALIZED_FIELD(Biomes, Internal::Conditioned<std::vector<VarInt>, &THIS::HasFullChunk>);
#else
        SERIALIZED_FIELD(AvailableSections, std::vector<unsigned long long int>);
        SERIALIZED_FIELD(Heightmaps, NBT::UnnamedValue);
        SERIALIZED_FIELD(Biomes, std::vector<VarInt>);
#endif
        SERIALIZED_FIELD(Buffer, std::vector<unsigned char>);
        SERIALIZED_FIELD(BlockEntitiesTags, std::vector<NBT::UnnamedValue>);

        DECLARE_READ_WRITE_SERIALIZE;
    };
} //ProtocolCraft
#endif
