#pragma once

#include <iostream>

#include "botcraft/Protocol/BaseMessage.hpp"
#include "botcraft/NBT/NBT.hpp"

#include "botcraft/Version.hpp"

namespace Botcraft
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
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575
			return 0x22;
#else
            #error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Chunk Data";
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

        const int GetPrimaryBitMask() const
        {
            return primary_bit_mask;
        }

#if PROTOCOL_VERSION > 442
        const NBT GetHeightmaps() const
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
            primary_bit_mask = ReadVarInt(iter, length);
#if PROTOCOL_VERSION > 442
            heightmaps.Read(iter, length);
#endif
#if PROTOCOL_VERSION > 551
			if (ground_up_continuous)
			{
				biomes = ReadArrayData<int>(iter, length, 1024);
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
            std::cerr << "Clientbound message" << std::endl;
        }

    private:
        int chunk_x;
        int chunk_z;
        bool ground_up_continuous;
        int primary_bit_mask;
#if PROTOCOL_VERSION > 442
        NBT heightmaps;
#endif
#if PROTOCOL_VERSION > 551
		std::vector<int> biomes;
#endif
        int size;
        std::vector<unsigned char> data;
        int number_block_entities;
        std::vector<unsigned char> block_entities;
    };
} //Botcraft