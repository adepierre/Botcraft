#if PROTOCOL_VERSION < 757 /* < 1.18 */
#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/NBT/NBT.hpp"

namespace ProtocolCraft
{

    class ClientboundLevelChunkPacket : public BaseMessage<ClientboundLevelChunkPacket>
    {
    public:

        static constexpr std::string_view packet_name = "Level Chunk";

#if PROTOCOL_VERSION > 551 /* > 1.14.4 */ && PROTOCOL_VERSION < 755 /* < 1.17 */
        DECLARE_CONDITION(FullChunk, GetFullChunk());
#endif

#if PROTOCOL_VERSION < 477 /* < 1.14 */
        DECLARE_FIELDS(
            (int, int, bool,      VarInt,            std::vector<unsigned char>, std::vector<NBT::UnnamedValue>),
            (X,   Z,   FullChunk, AvailableSections, Buffer,                     BlockEntitiesTags)
        );
#elif PROTOCOL_VERSION < 573 /* < 1.15 */
        DECLARE_FIELDS(
            (int, int, bool,      VarInt,            NBT::UnnamedValue, std::vector<unsigned char>, std::vector<NBT::UnnamedValue>),
            (X,   Z,   FullChunk, AvailableSections, Heightmaps,        Buffer,                     BlockEntitiesTags)
        );
#elif PROTOCOL_VERSION < 735 /* < 1.16 */
        DECLARE_FIELDS(
            (int, int, bool,      VarInt,            NBT::UnnamedValue, Internal::Conditioned<std::array<int, 1024>, &THIS::FullChunk>, std::vector<unsigned char>, std::vector<NBT::UnnamedValue>),
            (X,   Z,   FullChunk, AvailableSections, Heightmaps,        Biomes,                                                         Buffer,                     BlockEntitiesTags)
        );
#elif PROTOCOL_VERSION < 751 /* < 1.16.2 */
        DECLARE_FIELDS(
            (int, int, bool,      bool,          VarInt,            NBT::UnnamedValue, Internal::Conditioned<std::array<int, 1024>, &THIS::FullChunk>, std::vector<unsigned char>, std::vector<NBT::UnnamedValue>),
            (X,   Z,   FullChunk, IgnoreOldData, AvailableSections, Heightmaps,        Biomes,                                                         Buffer,                     BlockEntitiesTags)
        );
#elif PROTOCOL_VERSION < 755 /* < 1.17 */
        DECLARE_FIELDS(
            (int, int, bool,      VarInt,            NBT::UnnamedValue, Internal::Conditioned<std::vector<VarInt>, &THIS::FullChunk>, std::vector<unsigned char>, std::vector<NBT::UnnamedValue>),
            (X,   Z,   FullChunk, AvailableSections, Heightmaps,        Biomes,                                                       Buffer,                     BlockEntitiesTags)
        );
#else
        DECLARE_FIELDS(
            (int, int, std::vector<unsigned long long int>, NBT::UnnamedValue, std::vector<VarInt>, std::vector<unsigned char>, std::vector<NBT::UnnamedValue>),
            (X,   Z,   AvailableSections,                   Heightmaps,        Biomes,              Buffer,                     BlockEntitiesTags)
        );
#endif
        DECLARE_READ_WRITE_SERIALIZE;

        GETTER_SETTER(X);
        GETTER_SETTER(Z);
#if PROTOCOL_VERSION < 755 /* < 1.17 */
        GETTER_SETTER(FullChunk);
#endif
        GETTER_SETTER(AvailableSections);
        GETTER_SETTER(Buffer);
        GETTER_SETTER(BlockEntitiesTags);
#if PROTOCOL_VERSION > 442 /* > 1.13.2 */
        GETTER_SETTER(Heightmaps);
#endif
#if PROTOCOL_VERSION > 551 /* > 1.14.4 */
        GETTER_SETTER(Biomes);
#endif
#if PROTOCOL_VERSION > 730 /* > 1.15.2 */ && PROTOCOL_VERSION < 745 /* < 1.16.2 */
        GETTER_SETTER(IgnoreOldData);
#endif
    };
} //ProtocolCraft
#endif
