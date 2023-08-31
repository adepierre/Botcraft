#pragma once

#if PROTOCOL_VERSION < 757 /* < 1.18/.1 */
#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/NBT/NBT.hpp"

namespace ProtocolCraft
{

    class ClientboundLevelChunkPacket : public BaseMessage<ClientboundLevelChunkPacket>
    {
    public:
#if   PROTOCOL_VERSION == 340 /* 1.12.2 */
        static constexpr int packet_id = 0x20;
#elif PROTOCOL_VERSION == 393 /* 1.13 */ || PROTOCOL_VERSION == 401 /* 1.13.1 */ ||  \
      PROTOCOL_VERSION == 404 /* 1.13.2 */
        static constexpr int packet_id = 0x22;
#elif PROTOCOL_VERSION == 477 /* 1.14 */ || PROTOCOL_VERSION == 480 /* 1.14.1 */ ||  \
      PROTOCOL_VERSION == 485 /* 1.14.2 */ || PROTOCOL_VERSION == 490 /* 1.14.3 */ ||  \
      PROTOCOL_VERSION == 498 /* 1.14.4 */
        static constexpr int packet_id = 0x21;
#elif PROTOCOL_VERSION == 573 /* 1.15 */ || PROTOCOL_VERSION == 575 /* 1.15.1 */ ||  \
      PROTOCOL_VERSION == 578 /* 1.15.2 */
        static constexpr int packet_id = 0x22;
#elif PROTOCOL_VERSION == 735 /* 1.16 */ || PROTOCOL_VERSION == 736 /* 1.16.1 */
        static constexpr int packet_id = 0x21;
#elif PROTOCOL_VERSION == 751 /* 1.16.2 */ || PROTOCOL_VERSION == 753 /* 1.16.3 */ ||  \
      PROTOCOL_VERSION == 754 /* 1.16.4/5 */
        static constexpr int packet_id = 0x20;
#elif PROTOCOL_VERSION == 755 /* 1.17 */ || PROTOCOL_VERSION == 756 /* 1.17.1 */
        static constexpr int packet_id = 0x22;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Level Chunk";

        virtual ~ClientboundLevelChunkPacket() override
        {

        }
        
        void SetX(const int x_)
        {
            x = x_;
        }

        void SetZ(const int z_)
        {
            z = z_;
        }

#if PROTOCOL_VERSION > 730 /* > 1.15.2 */ && PROTOCOL_VERSION < 745 /* < 1.16.2 */
        void SetIgnoreOldData(const bool ignore_old_data_)
        {
            ignore_old_data = ignore_old_data_;
        }
#endif

#if PROTOCOL_VERSION < 755 /* < 1.17 */
        void SetAvailableSections(const int available_sections_)
#else
        void SetAvailableSections(const std::vector<unsigned long long int>& available_sections_)
#endif
        {
            available_sections = available_sections_;
        }

#if PROTOCOL_VERSION > 442 /* > 1.13.2 */
        void SetHeightmaps(const NBT::Value& heightmaps_)
        {
            heightmaps = heightmaps_;
        }
#endif

#if PROTOCOL_VERSION > 551 /* > 1.14.4 */
        void SetBiomes(const std::vector<int>& biomes_)
        {
            biomes = biomes_;
        }
#endif

        void SetBuffer(const std::vector<unsigned char>& buffer_)
        {
            buffer = buffer_;
        }

        void SetBlockEntitiesTags(const std::vector<NBT::Value>& block_entities_tags_)
        {
            block_entities_tags = block_entities_tags_;
        }

#if PROTOCOL_VERSION < 755 /* < 1.17 */
        void SetFullChunk(const bool full_chunk_)
        {
            full_chunk = full_chunk_;
        }
#endif


        int GetX() const
        {
            return x;
        }

        int GetZ() const
        {
            return z;
        }

#if PROTOCOL_VERSION > 730 /* > 1.15.2 */ && PROTOCOL_VERSION < 745 /* < 1.16.2 */
        bool GetIgnoreOldData() const
        {
            return ignore_old_data;
        }
#endif

#if PROTOCOL_VERSION < 755 /* < 1.17 */
        int GetAvailableSections() const
#else
        const std::vector<unsigned long long int>& GetAvailableSections() const
#endif
        {
            return available_sections;
        }

#if PROTOCOL_VERSION > 442 /* > 1.13.2 */
        const NBT::Value& GetHeightmaps() const
        {
            return heightmaps;
        }
#endif

#if PROTOCOL_VERSION > 551 /* > 1.14.4 */
        const std::vector<int>& GetBiomes() const
        {
            return biomes;
        }
#endif

        const std::vector<unsigned char>& GetBuffer() const
        {
            return buffer;
        }

        const std::vector<NBT::Value>& GetBlockEntitiesTags() const
        {
            return block_entities_tags;
        }

#if PROTOCOL_VERSION < 755 /* < 1.17 */
        bool GetFullChunk() const
        {
            return full_chunk;
        }
#endif

    protected:

        virtual void ReadImpl(ReadIterator &iter, size_t &length) override
        {
            x = ReadData<int>(iter, length);
            z = ReadData<int>(iter, length);
#if PROTOCOL_VERSION < 755 /* < 1.17 */
            full_chunk = ReadData<bool>(iter, length);
#endif
#if PROTOCOL_VERSION > 730 /* > 1.15.2 */ && PROTOCOL_VERSION < 745 /* < 1.16.2 */
            ignore_old_data = ReadData<bool>(iter, length);
#endif
#if PROTOCOL_VERSION < 755 /* < 1.17 */
            available_sections = ReadData<VarInt>(iter, length);
#else
            available_sections = ReadVector<unsigned long long int>(iter, length);
#endif
#if PROTOCOL_VERSION > 442 /* > 1.13.2 */
            heightmaps = ReadData<NBT::Value>(iter, length);
#endif
#if PROTOCOL_VERSION > 551 /* > 1.14.4 */
#if PROTOCOL_VERSION < 755 /* < 1.17 */
            if (full_chunk)
            {
#endif
#if PROTOCOL_VERSION > 738 /* > 1.16.1 */
                biomes = ReadVector<int>(iter, length,
                    [](ReadIterator& i, size_t& l)
                    {
                        return ReadData<VarInt>(i, l);
                    }
                );
#else
                biomes = std::vector<int>(1024);
                for (size_t i = 0; i < biomes.size(); ++i)
                {
                    biomes[i] = ReadData<int>(iter, length);
                }
#endif
#if PROTOCOL_VERSION < 755 /* < 1.17 */
            }
#endif
#endif
            buffer = ReadVector<unsigned char>(iter, length);
            block_entities_tags = ReadVector<NBT::Value>(iter, length);
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
            WriteData<int>(x, container);
            WriteData<int>(z, container);
#if PROTOCOL_VERSION < 755 /* < 1.17 */
            WriteData<bool>(full_chunk, container);
#endif
#if PROTOCOL_VERSION > 730 /* > 1.15.2 */ && PROTOCOL_VERSION < 745 /* < 1.16.2 */
            WriteData<bool>(ignore_old_data, container);
#endif
#if PROTOCOL_VERSION < 755 /* < 1.17 */
            WriteData<VarInt>(available_sections, container);
#else
            WriteVector<unsigned long long int>(available_sections, container);
#endif
#if PROTOCOL_VERSION > 442 /* > 1.13.2 */
            WriteData<NBT::Value>(heightmaps, container);
#endif
#if PROTOCOL_VERSION > 551 /* > 1.14.4 */
#if PROTOCOL_VERSION < 755 /* < 1.17 */
            if (full_chunk)
            {
#endif
#if PROTOCOL_VERSION > 738 /* > 1.16.1 */
                WriteVector<int>(biomes, container,
                    [](const int& i, WriteContainer& c)
                    {
                        WriteData<VarInt>(i, c);
                    }
                );
#else
                for (const auto i : biomes)
                {
                    WriteData<int>(i, container);
                }
#endif
#if PROTOCOL_VERSION < 755 /* < 1.17 */
            }
#endif
#endif
            WriteVector<unsigned char>(buffer, container);
            WriteVector<NBT::Value>(block_entities_tags, container);
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["x"] = x;
            output["z"] = z;
#if PROTOCOL_VERSION > 730 /* > 1.15.2 */ && PROTOCOL_VERSION < 745 /* < 1.16.2 */
            output["ignore_old_data"] = ignore_old_data;
#endif
#if PROTOCOL_VERSION < 755 /* < 1.17 */
            output["available_sections"] = available_sections;
#else
            output["available_sections"] = available_sections;
#endif
#if PROTOCOL_VERSION > 442 /* > 1.13.2 */
            output["heightmaps"] = heightmaps;
#endif
#if PROTOCOL_VERSION > 551 /* > 1.14.4 */
            output["biomes"] = "Vector of " + std::to_string(biomes.size()) + " int";
#endif
            output["buffer"] = "Vector of " + std::to_string(buffer.size()) + " unsigned char";

            output["block_entities_tags"] = block_entities_tags;

#if PROTOCOL_VERSION < 755 /* < 1.17 */
            output["full_chunk"] = full_chunk;
#endif

            return output;
        }

    private:
        int x = 0;
        int z = 0;
#if PROTOCOL_VERSION > 730 /* > 1.15.2 */ && PROTOCOL_VERSION < 745 /* < 1.16.2 */
        bool ignore_old_data = false;
#endif
#if PROTOCOL_VERSION < 755 /* < 1.17 */
        int available_sections = 0;
#else
        std::vector<unsigned long long int> available_sections;
#endif
#if PROTOCOL_VERSION > 442 /* > 1.13.2 */
        NBT::Value heightmaps;
#endif
#if PROTOCOL_VERSION > 551 /* > 1.14.4 */
        std::vector<int> biomes;
#endif
        std::vector<unsigned char> buffer;
        std::vector<NBT::Value> block_entities_tags;
#if PROTOCOL_VERSION < 755 /* < 1.17 */
        bool full_chunk = false;
#endif
    };
} //ProtocolCraft
#endif
