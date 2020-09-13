#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/NBT/NBT.hpp"

namespace ProtocolCraft
{

    class ChunkData : public BaseMessage<ChunkData>
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
#elif PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 // 1.16.2, 1.16.3
            return 0x20;
#else
            #error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Chunk Data";
        }
        
        void SetChunkX(const int chunk_x_)
        {
            chunk_x = chunk_x_;
        }

        void SetChunkZ(const int chunk_z_)
        {
            chunk_z = chunk_z_;
        }

        void SetGroundUpContinuous(const bool ground_up_continuous_)
        {
            ground_up_continuous = ground_up_continuous_;
        }

#if PROTOCOL_VERSION > 730 && PROTOCOL_VERSION < 745
        void SetIgnoreOldData(const bool ignore_old_data_)
        {
            ignore_old_data = ignore_old_data_;
        }
#endif

        void SetPrimaryBitMask(const int primary_bit_mask_)
        {
            primary_bit_mask = primary_bit_mask_;
        }

#if PROTOCOL_VERSION > 442
        void SetHeightmaps(const NBT& heightmaps_)
        {
            heightmaps = heightmaps_;
        }
#endif

#if PROTOCOL_VERSION > 738
        void SetBiomesLength(const int biomes_length_)
        {
            biomes_length = biomes_length_;
        }
#endif
#if PROTOCOL_VERSION > 551
        void SetBiomes(const std::vector<int>& biomes_)
        {
            biomes = biomes_;
        }
#endif

        void SetSize(const int size_)
        {
            size = size_;
        }

        void SetData(const std::vector<unsigned char>& data_)
        {
            data = data_;
        }

        void SetNumberBlockEntities(const int number_block_entities_)
        {
            number_block_entities = number_block_entities_;
        }

        void SetBlockEntitiesData(const std::vector<unsigned char>& block_entities_)
        {
            block_entities = block_entities_;
        }

        const int GetChunkX() const
        {
            return chunk_x;
        }

        const int GetChunkZ() const
        {
            return chunk_z;
        }

        const bool GetGroundUpContinuous() const
        {
            return ground_up_continuous;
        }

#if PROTOCOL_VERSION > 730 && PROTOCOL_VERSION < 745
        const bool GetIgnoreOldData() const
        {
            return ignore_old_data;
        }
#endif

        const int GetPrimaryBitMask() const
        {
            return primary_bit_mask;
        }

#if PROTOCOL_VERSION > 442
        const NBT& GetHeightmaps() const
        {
            return heightmaps;
        }
#endif

#if PROTOCOL_VERSION > 738
        const int GetBiomesLength() const
        {
            return biomes_length;
        }
#endif

#if PROTOCOL_VERSION > 551
		const std::vector<int>& GetBiomes() const
		{
			return biomes;
		}
#endif

        const int GetSize() const
        {
            return size;
        }

        const std::vector<unsigned char>& GetData() const
        {
            return data;
        }

        const int GetNumberBlockEntities() const
        {
            return number_block_entities;
        }

        const std::vector<unsigned char>& GetBlockEntitiesData() const
        {
            return block_entities;
        }

    protected:

        virtual void ReadImpl(ReadIterator &iter, size_t &length) override
        {
            chunk_x = ReadData<int>(iter, length);
            chunk_z = ReadData<int>(iter, length);
            ground_up_continuous = ReadData<bool>(iter, length);
#if PROTOCOL_VERSION > 730 && PROTOCOL_VERSION < 745
            ignore_old_data = ReadData<bool>(iter, length);
#endif
            primary_bit_mask = ReadVarInt(iter, length);
#if PROTOCOL_VERSION > 442
            heightmaps.Read(iter, length);
#endif
#if PROTOCOL_VERSION > 551
			if (ground_up_continuous)
			{
#if PROTOCOL_VERSION > 738
                biomes_length = ReadVarInt(iter, length);
                biomes = std::vector<int>(biomes_length);
                for (int i = 0; i < biomes_length; ++i)
                {
                    biomes[i] = ReadVarInt(iter, length);
                }
#else
                biomes = ReadArrayData<int>(iter, length, 1024);
#endif
			}
#endif
            size = ReadVarInt(iter, length);
            data = ReadByteArray(iter, length, size);
            number_block_entities = ReadVarInt(iter, length);
            if (number_block_entities > 0)
            {
                int remaining_size = length;
                block_entities = ReadArrayData<unsigned char>(iter, length, remaining_size);
            }
            else
            {
                block_entities.clear();
            }
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
            WriteData<int>(chunk_x, container);
            WriteData<int>(chunk_z, container);
            WriteData<bool>(ground_up_continuous, container);
#if PROTOCOL_VERSION > 730 && PROTOCOL_VERSION < 745
            WriteData<bool>(ignore_old_data, container);
#endif
            WriteVarInt(primary_bit_mask, container);
#if PROTOCOL_VERSION > 442
            heightmaps.Write(container);
#endif
#if PROTOCOL_VERSION > 551
            if (ground_up_continuous)
            {
#if PROTOCOL_VERSION > 738
                WriteVarInt(biomes_length, container);
                for (int i = 0; i < biomes_length; ++i)
                {
                    WriteVarInt(biomes[i], container);
                }
#else
                WriteArrayData(biomes, container);
#endif
            }
#endif
            WriteVarInt(size, container);
            WriteByteArray(data, container);
            WriteVarInt(number_block_entities, container);
            WriteArrayData<unsigned char>(block_entities, container);
        }

        virtual const picojson::value SerializeImpl() const override
        {
            picojson::value value(picojson::object_type, false);
            picojson::object& object = value.get<picojson::object>();

            object["chunk_x"] = picojson::value((double)chunk_x);
            object["chunk_z"] = picojson::value((double)chunk_z);
            object["ground_up_continuous"] = picojson::value(ground_up_continuous);
#if PROTOCOL_VERSION > 730 && PROTOCOL_VERSION < 745
            object["ignore_old_data"] = picojson::value(ignore_old_data);
#endif
            object["primary_bit_mask"] = picojson::value((double)primary_bit_mask);
#if PROTOCOL_VERSION > 442
            object["heightmaps"] = heightmaps.Serialize();
#endif
#if PROTOCOL_VERSION > 738
            object["biomes_length"] = picojson::value((double)biomes_length);
#endif
#if PROTOCOL_VERSION > 551
            object["biomes"] = picojson::value("Vector of " + std::to_string(biomes.size()) + " int");
#endif
            object["size"] = picojson::value((double)size);
            object["data"] = picojson::value("Vector of " + std::to_string(data.size()) + " unsigned char");
            object["number_block_entities"] = picojson::value((double)number_block_entities);
            object["block_entities"] = picojson::value("Vector of " + std::to_string(block_entities.size()) + " unsigned char");

            return value;
        }

    private:
        int chunk_x;
        int chunk_z;
        bool ground_up_continuous;
#if PROTOCOL_VERSION > 730 && PROTOCOL_VERSION < 745
        bool ignore_old_data;
#endif
        int primary_bit_mask;
#if PROTOCOL_VERSION > 442
        NBT heightmaps;
#endif
#if PROTOCOL_VERSION > 738
        int biomes_length;
#endif
#if PROTOCOL_VERSION > 551
		std::vector<int> biomes;
#endif
        int size;
        std::vector<unsigned char> data;
        int number_block_entities;
        std::vector<unsigned char> block_entities;
    };
} //ProtocolCraft