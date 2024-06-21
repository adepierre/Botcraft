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
            (int, int, bool,      VarInt,            NBT::UnnamedValue, std::vector<int>, std::vector<unsigned char>, std::vector<NBT::UnnamedValue>),
            (X,   Z,   FullChunk, AvailableSections, Heightmaps,        Biomes,           Buffer,                     BlockEntitiesTags)
        );
#elif PROTOCOL_VERSION < 751 /* < 1.16.2 */
        DECLARE_FIELDS(
            (int, int, bool,      bool,          VarInt,            NBT::UnnamedValue, std::vector<int>, std::vector<unsigned char>, std::vector<NBT::UnnamedValue>),
            (X,   Z,   FullChunk, IgnoreOldData, AvailableSections, Heightmaps,        Biomes,           Buffer,                     BlockEntitiesTags)
        );
#elif PROTOCOL_VERSION < 755 /* < 1.17 */
        DECLARE_FIELDS(
            (int, int, bool,      VarInt,            NBT::UnnamedValue, std::vector<VarInt>, std::vector<unsigned char>, std::vector<NBT::UnnamedValue>),
            (X,   Z,   FullChunk, AvailableSections, Heightmaps,        Biomes,              Buffer,                     BlockEntitiesTags)
        );
#else
        DECLARE_FIELDS(
            (int, int, std::vector<unsigned long long int>, NBT::UnnamedValue, std::vector<VarInt>, std::vector<unsigned char>, std::vector<NBT::UnnamedValue>),
            (X,   Z,   AvailableSections,                   Heightmaps,        Biomes,              Buffer,                     BlockEntitiesTags)
        );
#endif
        DECLARE_SERIALIZE;

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

    protected:

        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            SetX(ReadData<int>(iter, length));
            SetZ(ReadData<int>(iter, length));
#if PROTOCOL_VERSION < 755 /* < 1.17 */
            SetFullChunk(ReadData<bool>(iter, length));
#endif
#if PROTOCOL_VERSION > 730 /* > 1.15.2 */ && PROTOCOL_VERSION < 745 /* < 1.16.2 */
            SetIgnoreOldData(ReadData<bool>(iter, length));
#endif
#if PROTOCOL_VERSION < 755 /* < 1.17 */
            SetAvailableSections(ReadData<VarInt>(iter, length));
#else
            SetAvailableSections(ReadData<std::vector<unsigned long long int>>(iter, length));
#endif
#if PROTOCOL_VERSION > 442 /* > 1.13.2 */
            SetHeightmaps(ReadData<NBT::UnnamedValue>(iter, length));
#endif
#if PROTOCOL_VERSION > 551 /* > 1.14.4 */
#if PROTOCOL_VERSION < 755 /* < 1.17 */
            if (GetFullChunk())
            {
#endif
#if PROTOCOL_VERSION > 738 /* > 1.16.1 */
                SetBiomes(ReadData<std::vector<VarInt>>(iter, length));
#else
                std::vector<int> biomes = std::vector<int>(1024);
                for (size_t i = 0; i < biomes.size(); ++i)
                {
                    biomes[i] = ReadData<int>(iter, length);
                }
                SetBiomes(biomes);
#endif
#if PROTOCOL_VERSION < 755 /* < 1.17 */
            }
#endif
#endif
            SetBuffer(ReadData<std::vector<unsigned char>>(iter, length));
            SetBlockEntitiesTags(ReadData<std::vector<NBT::UnnamedValue>>(iter, length));
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<int>(GetX(), container);
            WriteData<int>(GetZ(), container);
#if PROTOCOL_VERSION < 755 /* < 1.17 */
            WriteData<bool>(GetFullChunk(), container);
#endif
#if PROTOCOL_VERSION > 730 /* > 1.15.2 */ && PROTOCOL_VERSION < 745 /* < 1.16.2 */
            WriteData<bool>(GetIgnoreOldData(), container);
#endif
#if PROTOCOL_VERSION < 755 /* < 1.17 */
            WriteData<VarInt>(GetAvailableSections(), container);
#else
            WriteData<std::vector<unsigned long long int>>(GetAvailableSections(), container);
#endif
#if PROTOCOL_VERSION > 442 /* > 1.13.2 */
            WriteData<NBT::UnnamedValue>(GetHeightmaps(), container);
#endif
#if PROTOCOL_VERSION > 551 /* > 1.14.4 */
#if PROTOCOL_VERSION < 755 /* < 1.17 */
            if (GetFullChunk())
            {
#endif
#if PROTOCOL_VERSION > 738 /* > 1.16.1 */
                WriteData<std::vector<VarInt>>(GetBiomes(), container);
#else
                for (const auto i : GetBiomes())
                {
                    WriteData<int>(i, container);
                }
#endif
#if PROTOCOL_VERSION < 755 /* < 1.17 */
            }
#endif
#endif
            WriteData<std::vector<unsigned char>>(GetBuffer(), container);
            WriteData<std::vector<NBT::UnnamedValue>>(GetBlockEntitiesTags(), container);
        }

    };
} //ProtocolCraft
#endif
