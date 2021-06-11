#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/NBT/NBT.hpp"

namespace ProtocolCraft
{

    class ClientboundLevelChunkPacket : public BaseMessage<ClientboundLevelChunkPacket>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 340 // 1.12.2
            return 0x20;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
            return 0x22;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
            return 0x21;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
			return 0x22;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16.0 or 1.16.1
            return 0x21;
#elif PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 || PROTOCOL_VERSION == 754 // 1.16.2, 1.16.3, 1.16.4, 1.16.5
            return 0x20;
#elif PROTOCOL_VERSION == 755 // 1.17
            return 0x22;
#else
            #error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Level Chunk";
        }

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

#if PROTOCOL_VERSION > 730 && PROTOCOL_VERSION < 745
        void SetIgnoreOldData(const bool ignore_old_data_)
        {
            ignore_old_data = ignore_old_data_;
        }
#endif

        void SetAvailableSections(const int available_sections_)
        {
            available_sections = available_sections_;
        }

#if PROTOCOL_VERSION > 442
        void SetHeightmaps(const NBT& heightmaps_)
        {
            heightmaps = heightmaps_;
        }
#endif

#if PROTOCOL_VERSION > 551
        void SetBiomes(const std::vector<int>& biomes_)
        {
            biomes = biomes_;
        }
#endif

        void SetBuffer(const std::vector<unsigned char>& buffer_)
        {
            buffer = buffer_;
        }

        void SetBlockEntitiesTags(const std::vector<NBT>& block_entities_tags_)
        {
            block_entities_tags = block_entities_tags_;
        }

        void SetFullChunk(const bool full_chunk_)
        {
            full_chunk = full_chunk_;
        }


        const int GetX() const
        {
            return x;
        }

        const int GetZ() const
        {
            return z;
        }

#if PROTOCOL_VERSION > 730 && PROTOCOL_VERSION < 745
        const bool GetIgnoreOldData() const
        {
            return ignore_old_data;
        }
#endif

        const int GetAvailableSections() const
        {
            return available_sections;
        }

#if PROTOCOL_VERSION > 442
        const NBT& GetHeightmaps() const
        {
            return heightmaps;
        }
#endif

#if PROTOCOL_VERSION > 551
		const std::vector<int>& GetBiomes() const
		{
			return biomes;
		}
#endif

        const std::vector<unsigned char>& GetBuffer() const
        {
            return buffer;
        }

        const std::vector<NBT>& GetBlockEntitiesTags() const
        {
            return block_entities_tags;
        }

        const bool GetFullChunk() const
        {
            return full_chunk;
        }

    protected:

        virtual void ReadImpl(ReadIterator &iter, size_t &length) override
        {
            x = ReadData<int>(iter, length);
            z = ReadData<int>(iter, length);
            full_chunk = ReadData<bool>(iter, length);
#if PROTOCOL_VERSION > 730 && PROTOCOL_VERSION < 745
            ignore_old_data = ReadData<bool>(iter, length);
#endif
            available_sections = ReadVarInt(iter, length);
#if PROTOCOL_VERSION > 442
            heightmaps.Read(iter, length);
#endif
#if PROTOCOL_VERSION > 551
			if (full_chunk)
			{
#if PROTOCOL_VERSION > 738
                const int biomes_size = ReadVarInt(iter, length);
                biomes = std::vector<int>(biomes_size);
                for (int i = 0; i < biomes_size; ++i)
                {
                    biomes[i] = ReadVarInt(iter, length);
                }
#else
                biomes = ReadArrayData<int>(iter, length, 1024);
#endif
			}
#endif
            const int buffer_size = ReadVarInt(iter, length);
            buffer = ReadByteArray(iter, length, buffer_size);
            const int num_block_entities_tags = ReadVarInt(iter, length);
            block_entities_tags = std::vector<NBT>(num_block_entities_tags);
            for (int i = 0; i < num_block_entities_tags; ++i)
            {
                block_entities_tags[i].Read(iter, length);
            }
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
            WriteData<int>(x, container);
            WriteData<int>(z, container);
            WriteData<bool>(full_chunk, container);
#if PROTOCOL_VERSION > 730 && PROTOCOL_VERSION < 745
            WriteData<bool>(ignore_old_data, container);
#endif
            WriteVarInt(available_sections, container);
#if PROTOCOL_VERSION > 442
            heightmaps.Write(container);
#endif
#if PROTOCOL_VERSION > 551
            if (full_chunk)
            {
#if PROTOCOL_VERSION > 738
                WriteVarInt(biomes.size(), container);
                for (int i = 0; i < biomes.size(); ++i)
                {
                    WriteVarInt(biomes[i], container);
                }
#else
                WriteArrayData(biomes, container);
#endif
            }
#endif
            WriteVarInt(buffer.size(), container);
            WriteByteArray(buffer, container);
            WriteVarInt(block_entities_tags.size(), container);
            for (int i = 0; i < block_entities_tags.size(); ++i)
            {
                block_entities_tags[i].Write(container);
            }
        }

        virtual const picojson::value SerializeImpl() const override
        {
            picojson::value value(picojson::object_type, false);
            picojson::object& object = value.get<picojson::object>();

            object["x"] = picojson::value((double)x);
            object["z"] = picojson::value((double)z);
#if PROTOCOL_VERSION > 730 && PROTOCOL_VERSION < 745
            object["ignore_old_data"] = picojson::value(ignore_old_data);
#endif
            object["available_sections"] = picojson::value((double)available_sections);
#if PROTOCOL_VERSION > 442
            object["heightmaps"] = heightmaps.Serialize();
#endif
#if PROTOCOL_VERSION > 551
            object["biomes"] = picojson::value("Vector of " + std::to_string(biomes.size()) + " int");
#endif
            object["buffer"] = picojson::value("Vector of " + std::to_string(buffer.size()) + " unsigned char");
            object["block_entities_tags"] = picojson::value("Vector of " + std::to_string(block_entities_tags.size()) + " unsigned char");

            object["block_entities_tags"] = picojson::value(picojson::array_type, false);
            picojson::array& array_block_entities_tags = object["block_entities_tags"].get<picojson::array>();
            for (int i = 0; i < block_entities_tags.size(); ++i)
            {
                array_block_entities_tags.push_back(block_entities_tags[i].Serialize());
            }

            object["full_chunk"] = picojson::value(full_chunk);

            return value;
        }

    private:
        int x;
        int z;
#if PROTOCOL_VERSION > 730 && PROTOCOL_VERSION < 745
        bool ignore_old_data;
#endif
        int available_sections;
#if PROTOCOL_VERSION > 442
        NBT heightmaps;
#endif
#if PROTOCOL_VERSION > 551
		std::vector<int> biomes;
#endif
        std::vector<unsigned char> buffer;
        std::vector<NBT> block_entities_tags;
        bool full_chunk;
    };
} //ProtocolCraft