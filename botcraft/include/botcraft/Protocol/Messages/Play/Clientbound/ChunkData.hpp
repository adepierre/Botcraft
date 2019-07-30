#pragma once

#include <iostream>

#include "botcraft/Protocol/BaseMessage.hpp"

#include "botcraft/Game/World/Chunk.hpp"

#include "botcraft/Version.hpp"

#include "botcraft/NBT/NBT.hpp"
#include "botcraft/NBT/TagInt.hpp"

namespace Botcraft
{
#if PROTOCOL_VERSION < 347
    static const unsigned int DIRECT_NUM_BITS_PER_BLOCK = 13; //ceil(log2(total_number_of_block_states))
#else
    static const unsigned int DIRECT_NUM_BITS_PER_BLOCK = 14; //ceil(log2(total_number_of_block_states))
#endif
    enum class Palette
    {
        SectionPalette,
        GlobalPalette
    };

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

        void DeserializeData(std::shared_ptr<Chunk> chunk) const
        {
            std::vector<unsigned char>::const_iterator iter = data.begin();
            size_t length = data.size();

            if (data.size() == 0)
            {
                std::cerr << "Error, cannot load chunk data without data" << std::endl;
                return;
            }

            if (!chunk)
            {
                std::cerr << "Error, cannot load chunk data in a NULL chunk" << std::endl;
                return;
            }

            //The chunck sections
            for (int sectionY = 0; sectionY < CHUNK_HEIGHT / SECTION_HEIGHT; ++sectionY)
            {
                if (!(primary_bit_mask & (1 << sectionY)))
                {
                    continue;
                }

#if PROTOCOL_VERSION > 404
                short block_count = ReadData<short>(iter, length);
#endif
                unsigned char bits_per_block = ReadData<unsigned char>(iter, length);

                Palette palette_type = (bits_per_block <= 8 ? Palette::SectionPalette : Palette::GlobalPalette);

#if PROTOCOL_VERSION < 384
                int palette_length = ReadVarInt(iter, length);
#else
                int palette_length = 0;
                if (palette_type != Palette::GlobalPalette)
                {
                    palette_length = ReadVarInt(iter, length);
                }
#endif
                std::vector<int> palette(palette_length);
                if (palette_type != Palette::GlobalPalette)
                {
                    if (bits_per_block < 4)
                    {
                        std::cerr << "Error, bits per block must be between 4 and 8 when using a palette. Discarding packet" << std::endl;
                        return;
                    }

                    for (int i = 0; i < palette_length; ++i)
                    {
                        palette[i] = ReadVarInt(iter, length);
                    }
                }
                else
                {
                    if (palette_length != 0)
                    {
                        std::cerr << "Error, palette length should be 0 for global palette. Discarding packet" << std::endl;
                        return;
                    }
                }

                //A mask 0...01..1 with bits_per_block ones
                unsigned int individual_value_mask = (unsigned int)((1 << bits_per_block) - 1);

                //Data array length
                int data_array_size = ReadVarInt(iter, length);

                //Data array
                std::vector<unsigned long long int> data_array(data_array_size);
                for (int i = 0; i < data_array_size; ++i)
                {
                    data_array[i] = ReadData<unsigned long long int>(iter, length);
                }

                //Blocks data
                for (int block_y = 0; block_y < SECTION_HEIGHT; ++block_y)
                {
                    for (int block_z = 0; block_z < CHUNK_WIDTH; ++block_z)
                    {
                        for (int block_x = 0; block_x < CHUNK_WIDTH; ++block_x)
                        {
                            int block_index = (((block_y * SECTION_HEIGHT) + block_z) * CHUNK_WIDTH) + block_x;
                            int start_long_index = (block_index * bits_per_block) / 64;
                            int start_offset = (block_index * bits_per_block) % 64;
                            int end_long_index = ((block_index + 1) * bits_per_block - 1) / 64;

                            unsigned int raw_id;
                            if (start_long_index == end_long_index)
                            {
                                raw_id = (unsigned int)(data_array[start_long_index] >> start_offset);
                            }
                            else
                            {
                                int end_offset = 64 - start_offset;
                                raw_id = (unsigned int)(data_array[start_long_index] >> start_offset | data_array[end_long_index] << end_offset);
                            }
                            raw_id &= individual_value_mask;

                            if (palette_type != Palette::GlobalPalette)
                            {
                                raw_id = palette[raw_id];
                            }

#if PROTOCOL_VERSION < 347
                            unsigned int id;
                            unsigned char metadata;

                            Blockstate::IdToIdMetadata(raw_id, id, metadata);

                            chunk->SetBlock(Position(block_x, block_y + sectionY * SECTION_HEIGHT, block_z), id, metadata);
#else
                            chunk->SetBlock(Position(block_x, block_y + sectionY * SECTION_HEIGHT, block_z), raw_id);
#endif
                        }
                    }
                }

#if PROTOCOL_VERSION <= 404
                //Block light
                for (int block_y = 0; block_y < SECTION_HEIGHT; ++block_y)
                {
                    for (int block_z = 0; block_z < CHUNK_WIDTH; ++block_z)
                    {
                        for (int block_x = 0; block_x < CHUNK_WIDTH; block_x += 2)
                        {
                            unsigned char two_light_values = ReadData<unsigned char>(iter, length);

                            chunk->SetBlockLight(Position(block_x, block_y + sectionY * SECTION_HEIGHT, block_z), two_light_values & 0x0F);
                            chunk->SetBlockLight(Position(block_x + 1, block_y + sectionY * SECTION_HEIGHT, block_z), (two_light_values >> 4) & 0x0F);
                        }
                    }
                }

                //Sky light
                if (chunk->GetDimension() == Dimension::Overworld)
                {
                    for (int block_y = 0; block_y < SECTION_HEIGHT; ++block_y)
                    {
                        for (int block_z = 0; block_z < CHUNK_WIDTH; ++block_z)
                        {
                            for (int block_x = 0; block_x < CHUNK_WIDTH; block_x += 2)
                            {
                                unsigned char two_light_values = ReadData<unsigned char>(iter, length);

                                chunk->SetSkyLight(Position(block_x, block_y + sectionY * SECTION_HEIGHT, block_z), two_light_values & 0x0F);
                                chunk->SetSkyLight(Position(block_x + 1, block_y + sectionY * SECTION_HEIGHT, block_z), (two_light_values >> 4) & 0x0F);
                            }
                        }
                    }
                }
#endif
            }

            //The biomes
            if (ground_up_continuous)
            {
                for (int block_z = 0; block_z < CHUNK_WIDTH; ++block_z)
                {
                    for (int block_x = 0; block_x < CHUNK_WIDTH; ++block_x)
                    {
#if PROTOCOL_VERSION < 358 
                        chunk->SetBiome(block_x, block_z, ReadData<unsigned char>(iter, length));
#else
                        chunk->SetBiome(block_x, block_z, ReadData<int>(iter, length));
#endif
                    }
                }
            }

            // Block entities data
            chunk->GetBlockEntitiesData().clear();
            auto iter_entities = block_entities.begin();
            size_t length_entitites = block_entities.size();

            for (int i = 0; i < number_block_entities; ++i)
            {
                std::shared_ptr<NBT> current_nbt = std::shared_ptr<NBT>(new NBT);
                current_nbt->Read(iter_entities, length_entitites);

                if (current_nbt->HasData())
                {
                    std::shared_ptr<TagInt> tag_x = std::dynamic_pointer_cast<TagInt>(current_nbt->GetTag("x"));
                    std::shared_ptr<TagInt> tag_y = std::dynamic_pointer_cast<TagInt>(current_nbt->GetTag("y"));
                    std::shared_ptr<TagInt> tag_z = std::dynamic_pointer_cast<TagInt>(current_nbt->GetTag("z"));

                    if (tag_x && tag_y && tag_z)
                    {
                        auto &block_entity_data_map = chunk->GetBlockEntitiesData();
                        block_entity_data_map[Position(tag_x->GetValue(), tag_y->GetValue(), tag_z->GetValue())] = current_nbt;
                    }
                }
            }
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
        int size;
        std::vector<unsigned char> data;
        int number_block_entities;
        std::vector<unsigned char> block_entities;
    };
} //Botcraft