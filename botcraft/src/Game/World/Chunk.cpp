#include "botcraft/Game/World/Chunk.hpp"
#include "botcraft/Game/World/Section.hpp"
#include "botcraft/Utilities/Logger.hpp"

using namespace ProtocolCraft;

namespace Botcraft
{
    enum class Palette
    {
#if PROTOCOL_VERSION > 756
        SingleValue,
#endif
        SectionPalette,
        GlobalPalette
    };

#if PROTOCOL_VERSION < 719
    Chunk::Chunk(const Dimension &dim)
#elif PROTOCOL_VERSION < 757
    Chunk::Chunk(const std::string& dim)
#else
    Chunk::Chunk(const int min_y_, const unsigned int height_, const std::string& dim)
#endif
    {
        dimension = dim;
#if PROTOCOL_VERSION > 756
        height = height_;
        min_y = min_y_;
#endif
#if PROTOCOL_VERSION < 358
        biomes = std::vector<unsigned char>(CHUNK_WIDTH * CHUNK_WIDTH, 0);
#elif PROTOCOL_VERSION < 552
        biomes = std::vector<int>(CHUNK_WIDTH * CHUNK_WIDTH, 0);
#else
        // Each section has 64 biomes, one for each 4*4*4 cubes
        biomes = std::vector<int>(64 * height / SECTION_HEIGHT, 0);
#endif
        sections = std::vector<std::shared_ptr<Section> >(height / SECTION_HEIGHT);

#if USE_GUI
        modified_since_last_rendered = true;
#endif
    }

    Chunk::Chunk(const Chunk& c)
    {
        dimension = c.dimension;
        biomes = c.biomes;

#if PROTOCOL_VERSION > 756
        height = c.height;
        min_y = c.min_y;
#endif

        sections = std::vector<std::shared_ptr<Section> >(height / SECTION_HEIGHT);
        for (int i = 0; i < c.sections.size(); i++)
        {
            if (c.sections[i] == nullptr)
            {
                sections[i] = nullptr;
            }
            else
            {
                sections[i] = std::make_shared<Section>(*c.sections[i]);
            }
        }

        for (auto it = c.block_entities_data.begin(); it != c.block_entities_data.end(); it++)
        {
            block_entities_data[it->first] = std::make_shared<NBT::Value>(*it->second);
        }
    }

    const Position Chunk::BlockCoordsToChunkCoords(const Position& pos)
    {
        return Position(
            static_cast<int>(std::floor(pos.x / static_cast<double>(CHUNK_WIDTH))),
            0,
            static_cast<int>(std::floor(pos.z / static_cast<double>(CHUNK_WIDTH)))
        );
    }

    const int Chunk::GetMinY() const
    {
        return min_y;
    }

    const int Chunk::GetHeight() const
    {
        return height;
    }

#if USE_GUI
    const bool Chunk::GetModifiedSinceLastRender() const
    {
        return modified_since_last_rendered;
    }

    void Chunk::SetModifiedSinceLastRender(const bool b)
    {
        modified_since_last_rendered = b;
    }
#endif

#if PROTOCOL_VERSION < 757
#if PROTOCOL_VERSION < 552
    void Chunk::LoadChunkData(const std::vector<unsigned char>& data, const int primary_bit_mask, const bool ground_up_continuous)
#elif PROTOCOL_VERSION < 755
    void Chunk::LoadChunkData(const std::vector<unsigned char>& data, const int primary_bit_mask)
#else
    void Chunk::LoadChunkData(const std::vector<unsigned char>& data, const std::vector<unsigned long long int>& primary_bit_mask)
#endif
    {
        std::vector<unsigned char>::const_iterator iter = data.begin();
        size_t length = data.size();

        if (data.size() == 0)
        {
            LOG_ERROR("Cannot load chunk data without data");
            return;
        }

        //The chunck sections
        for (int sectionY = 0; sectionY < height / SECTION_HEIGHT; ++sectionY)
        {
#if PROTOCOL_VERSION < 755
            if (!(primary_bit_mask & (1 << sectionY)))
#else
            if (!(primary_bit_mask[sectionY / 64] & (1 << (sectionY % 64))))
#endif
            {
                continue;
            }

#if PROTOCOL_VERSION > 404
            short block_count = ReadData<short>(iter, length);
#endif
            unsigned char bits_per_block = ReadData<unsigned char>(iter, length);

            Palette palette_type = (bits_per_block <= 8 ? Palette::SectionPalette : Palette::GlobalPalette);

#if PROTOCOL_VERSION < 384
            int palette_length = ReadData<VarInt>(iter, length);
#else
            int palette_length = 0;
            if (palette_type != Palette::GlobalPalette)
            {
                palette_length = ReadData<VarInt>(iter, length);
            }
#endif
            std::vector<int> palette(palette_length);
            if (palette_type != Palette::GlobalPalette)
            {
                if (bits_per_block < 4)
                {
                    LOG_ERROR("Bits per block must be between 4 and 8 when using a palette (current: " << bits_per_block << "). Stop loading current chunk data");
                    return;
                }

                for (int i = 0; i < palette_length; ++i)
                {
                    palette[i] = ReadData<VarInt>(iter, length);
                }
            }
            else
            {
                if (palette_length != 0)
                {
                    LOG_ERROR("Palette length should be 0 for global palette (current: " << palette_length << "). Stop loading current chunk data");
                    return;
                }
            }

            //A mask 0...01..1 with bits_per_block ones
            unsigned int individual_value_mask = (unsigned int)((1 << bits_per_block) - 1);

            //Data array length
            int data_array_size = ReadData<VarInt>(iter, length);

            //Data array
            std::vector<unsigned long long int> data_array(data_array_size);
            for (int i = 0; i < data_array_size; ++i)
            {
                data_array[i] = ReadData<unsigned long long int>(iter, length);
            }

            //Blocks data
#if PROTOCOL_VERSION > 712
            int bit_offset = 0;
#endif
            Position pos;
            for (int block_y = 0; block_y < SECTION_HEIGHT; ++block_y)
            {
                pos.y = block_y + sectionY * SECTION_HEIGHT + min_y;
                for (int block_z = 0; block_z < CHUNK_WIDTH; ++block_z)
                {
                    pos.z = block_z;
                    for (int block_x = 0; block_x < CHUNK_WIDTH; ++block_x)
                    {
                        pos.x = block_x;
#if PROTOCOL_VERSION > 712
                        // From protocol version 713, the compacted array format has been adjusted so that
                        //individual entries no longer span across multiple longs
                        if (64 - (bit_offset % 64) < bits_per_block)
                        {
                            bit_offset += 64 - (bit_offset % 64);
                        }
                        int start_long_index = bit_offset / 64;
                        int end_long_index = start_long_index;
                        int start_offset = bit_offset % 64;
                        bit_offset += bits_per_block;
#else
                        int block_index = (((block_y * SECTION_HEIGHT) + block_z) * CHUNK_WIDTH) + block_x;
                        int start_long_index = (block_index * bits_per_block) / 64;
                        int start_offset = (block_index * bits_per_block) % 64;
                        int end_long_index = ((block_index + 1) * bits_per_block - 1) / 64;
#endif
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

                        SetBlock(pos, id, metadata);
#else
                        SetBlock(pos, raw_id);
#endif
                    }
                }
            }

#if PROTOCOL_VERSION <= 404
            //Block light
            for (int block_y = 0; block_y < SECTION_HEIGHT; ++block_y)
            {
                pos.y = block_y + sectionY * SECTION_HEIGHT + min_y;
                for (int block_z = 0; block_z < CHUNK_WIDTH; ++block_z)
                {
                    pos.z = block_z;
                    for (int block_x = 0; block_x < CHUNK_WIDTH; block_x += 2)
                    {
                        pos.x = block_x;
                        unsigned char two_light_values = ReadData<unsigned char>(iter, length);

                        SetBlockLight(pos, two_light_values & 0x0F);
                        pos.x = block_x + 1;
                        SetBlockLight(pos, (two_light_values >> 4) & 0x0F);
                    }
                }
            }

            //Sky light
            if (GetDimension() == Dimension::Overworld)
            {
                for (int block_y = 0; block_y < SECTION_HEIGHT; ++block_y)
                {
                    pos.y = block_y + sectionY * SECTION_HEIGHT + min_y;
                    for (int block_z = 0; block_z < CHUNK_WIDTH; ++block_z)
                    {
                        pos.z = block_z;
                        for (int block_x = 0; block_x < CHUNK_WIDTH; block_x += 2)
                        {
                            pos.x = block_x;
                            unsigned char two_light_values = ReadData<unsigned char>(iter, length);

                            SetSkyLight(pos, two_light_values & 0x0F);
                            pos.x = block_x + 1;
                            SetSkyLight(pos, (two_light_values >> 4) & 0x0F);
                        }
                    }
                }
            }
#endif
        }

#if PROTOCOL_VERSION < 552
        //The biomes
        if (ground_up_continuous)
        {
            for (int block_z = 0; block_z < CHUNK_WIDTH; ++block_z)
            {
                for (int block_x = 0; block_x < CHUNK_WIDTH; ++block_x)
                {
#if PROTOCOL_VERSION < 358 
                    SetBiome(block_x, block_z, ReadData<unsigned char>(iter, length));
#else
                    SetBiome(block_x, block_z, ReadData<int>(iter, length));
#endif
                }
            }
        }
#endif
#if USE_GUI
        modified_since_last_rendered = true;
#endif
    }
#else
    void Chunk::LoadChunkData(const std::vector<unsigned char>& data)
    {
        std::vector<unsigned char>::const_iterator iter = data.begin();
        size_t length = data.size();

        if (data.size() == 0)
        {
            LOG_ERROR("Cannot load chunk data without data");
            return;
        }

        //The chunck sections
        for (int sectionY = 0; sectionY < height / SECTION_HEIGHT; ++sectionY)
        {
            short block_count = ReadData<short>(iter, length);

            // Paletted block states
            unsigned char bits_per_block = ReadData<unsigned char>(iter, length);

            Palette palette_type = (bits_per_block == 0 ? Palette::SingleValue : (bits_per_block <= 8 ? Palette::SectionPalette : Palette::GlobalPalette));

            int palette_length = 0;
            int palette_value = 0;
            std::vector<int> palette;
            switch (palette_type)
            {
            case Botcraft::Palette::SingleValue:
                palette_value = ReadData<VarInt>(iter, length);
                break;
            case Botcraft::Palette::SectionPalette:
                if (bits_per_block < 4)
                {
                    bits_per_block = 4;
                }
                palette_length = ReadData<VarInt>(iter, length);
                palette = std::vector<int>(palette_length);

                for (int i = 0; i < palette_length; ++i)
                {
                    palette[i] = ReadData<VarInt>(iter, length);
                }
                break;
            case Botcraft::Palette::GlobalPalette:
                break;
            default:
                break;
            }

            //A mask 0...01..1 with bits_per_block ones
            unsigned int individual_value_mask = (unsigned int)((1 << bits_per_block) - 1);

            //Data array length
            int data_array_size = ReadData<VarInt>(iter, length);

            //Data array
            std::vector<unsigned long long int> data_array(data_array_size);
            for (int i = 0; i < data_array_size; ++i)
            {
                data_array[i] = ReadData<unsigned long long int>(iter, length);
            }

            //Blocks data
            int bit_offset = 0;
            Position pos;
            if (block_count != 0)
            {
                for (int block_y = 0; block_y < SECTION_HEIGHT; ++block_y)
                {
                    pos.y = block_y + sectionY * SECTION_HEIGHT + min_y;
                    for (int block_z = 0; block_z < CHUNK_WIDTH; ++block_z)
                    {
                        pos.z = block_z;
                        for (int block_x = 0; block_x < CHUNK_WIDTH; ++block_x)
                        {
                            pos.x = block_x;
                            if (palette_type == Palette::SingleValue)
                            {
                                SetBlock(pos, palette_value);
                                continue;
                            }

                            // Entries don't span across multiple longs
                            if (64 - (bit_offset % 64) < bits_per_block)
                            {
                                bit_offset += 64 - (bit_offset % 64);
                            }
                            int start_long_index = bit_offset / 64;
                            int end_long_index = start_long_index;
                            int start_offset = bit_offset % 64;
                            bit_offset += bits_per_block;

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

                            if (palette_type == Palette::SectionPalette)
                            {
                                raw_id = palette[raw_id];
                            }

                            SetBlock(pos, raw_id);
                        }
                    }
                }
            }
            else
            {
                sections[sectionY] = nullptr;
            }


            // Paletted biomes
            unsigned char bits_per_biome = ReadData<unsigned char>(iter, length);

            palette_type = (bits_per_biome == 0 ? Palette::SingleValue : (bits_per_biome <= 3 ? Palette::SectionPalette : Palette::GlobalPalette));

            switch (palette_type)
            {
            case Botcraft::Palette::SingleValue:
                palette_value = ReadData<VarInt>(iter, length);
                break;
            case Botcraft::Palette::SectionPalette:
                palette_length = ReadData<VarInt>(iter, length);
                palette = std::vector<int>(palette_length);
                for (int i = 0; i < palette_length; ++i)
                {
                    palette[i] = ReadData<VarInt>(iter, length);
                }
                break;
            case Botcraft::Palette::GlobalPalette:
                break;
            default:
                break;
            }

            //A mask 0...01..1 with bits_per_biome ones
            individual_value_mask = (unsigned int)((1 << bits_per_biome) - 1);

            //Data array length
            data_array_size = ReadData<VarInt>(iter, length);

            //Data array
            data_array = std::vector<unsigned long long int>(data_array_size);
            for (int i = 0; i < data_array_size; ++i)
            {
                data_array[i] = ReadData<unsigned long long int>(iter, length);
            }

            //Biomes data
            bit_offset = 0;
            for (int block_y = 0; block_y < SECTION_HEIGHT / 4; ++block_y)
            {
                for (int block_z = 0; block_z < CHUNK_WIDTH / 4; ++block_z)
                {
                    for (int block_x = 0; block_x < CHUNK_WIDTH / 4; ++block_x)
                    {
                        const int biome_index = sectionY * 64 + block_y * 16 + block_z * 4 + block_x;
                        if (palette_type == Palette::SingleValue)
                        {
                            SetBiome(biome_index, palette_value);
                            continue;
                        }

                        // Entries don't span across multiple longs
                        if (64 - (bit_offset % 64) < bits_per_biome)
                        {
                            bit_offset += 64 - (bit_offset % 64);
                        }
                        int start_long_index = bit_offset / 64;
                        int end_long_index = start_long_index;
                        int start_offset = bit_offset % 64;
                        bit_offset += bits_per_biome;

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

                        if (palette_type == Palette::SectionPalette)
                        {
                            raw_id = palette[raw_id];
                        }

                        SetBiome(biome_index, raw_id);
                    }
                }
            }
        }
#if USE_GUI
        modified_since_last_rendered = true;
#endif
    }
#endif

#if PROTOCOL_VERSION < 757
    void Chunk::LoadChunkBlockEntitiesData(const std::vector<NBT::Value>& block_entities)
#else
    void Chunk::LoadChunkBlockEntitiesData(const std::vector<BlockEntityInfo>& block_entities)
#endif
    {
        // Block entities data
        block_entities_data.clear();

        for (int i = 0; i < block_entities.size(); ++i)
        {
#if PROTOCOL_VERSION < 757
            if (block_entities[i].HasData())
            {
                if (block_entities[i].contains("x") &&
                    block_entities[i]["x"].is<int>() &&
                    block_entities[i].contains("y") &&
                    block_entities[i]["y"].is<int>() &&
                    block_entities[i].contains("z") &&
                    block_entities[i]["z"].is<int>())
                {
                    block_entities_data[Position((block_entities[i]["x"].get<int>() % CHUNK_WIDTH + CHUNK_WIDTH) % CHUNK_WIDTH, block_entities[i]["y"].get<int>(), (block_entities[i]["z"].get<int>() % CHUNK_WIDTH + CHUNK_WIDTH) % CHUNK_WIDTH)] = std::make_shared<NBT::Value>(block_entities[i]);
                }
            }
#else
            const int x = (block_entities[i].GetPackedXZ() & 15) << 4;
            const int z = (block_entities[i].GetPackedXZ() & 15);
            // And what about the type ???
            block_entities_data[Position((x % CHUNK_WIDTH + CHUNK_WIDTH) % CHUNK_WIDTH, block_entities[i].GetY(), (z % CHUNK_WIDTH + CHUNK_WIDTH) % CHUNK_WIDTH)] = std::make_shared<NBT::Value>(block_entities[i].GetTag());
#endif
        }

#if USE_GUI
        modified_since_last_rendered = true;
#endif
    }

    void Chunk::SetBlockEntityData(const Position& pos, const ProtocolCraft::NBT::Value& block_entity)
    {
        if (pos.x < -1 || pos.x > CHUNK_WIDTH || pos.y < min_y || pos.y > height + min_y - 1 || pos.z < -1 || pos.z > CHUNK_WIDTH)
        {
            return;
        }

        block_entities_data[pos] = std::make_shared<NBT::Value>(block_entity);

#if USE_GUI
        modified_since_last_rendered = true;
#endif
    }

    void Chunk::RemoveBlockEntityData(const Position& pos)
    {
        block_entities_data.erase(pos);
    }

    const std::shared_ptr<NBT::Value> Chunk::GetBlockEntityData(const Position& pos) const
    {
        auto it = block_entities_data.find(pos);
        if (it == block_entities_data.end())
        {
            return nullptr;
        }

        return it->second;
    }

    const Block *Chunk::GetBlock(const Position &pos) const
    {
        if (pos.x < -1 || pos.x > CHUNK_WIDTH || pos.y < min_y || pos.y > height + min_y - 1 || pos.z < -1 || pos.z > CHUNK_WIDTH)
        {
            return nullptr;
        }

        if (!sections[(pos.y - min_y) / SECTION_HEIGHT])
        {
            return nullptr;
        }

        return sections[(pos.y - min_y) / SECTION_HEIGHT]->data_blocks.data() + (((pos.y - min_y) % SECTION_HEIGHT) * (CHUNK_WIDTH + 2) * (CHUNK_WIDTH + 2) + (pos.z + 1) * (CHUNK_WIDTH + 2) + pos.x + 1);
    }

#if PROTOCOL_VERSION < 347
    void Chunk::SetBlock(const Position &pos, const unsigned int id, unsigned char metadata, const int model_id)
#else
    void Chunk::SetBlock(const Position &pos, const unsigned int id, const int model_id)
#endif
    {
        if (pos.x < -1 || pos.x > CHUNK_WIDTH || pos.y < min_y || pos.y > height + min_y - 1 || pos.z < -1 || pos.z > CHUNK_WIDTH)
        {
            return;
        }

        if (!sections[(pos.y  - min_y) / SECTION_HEIGHT])
        {
            if (id == 0)
            {
                return;
            }
            else
            {
                AddSection((pos.y - min_y) / SECTION_HEIGHT);
            }
        }
        Block *block = sections[(pos.y - min_y) / SECTION_HEIGHT]->data_blocks.data() + (((pos.y - min_y) % SECTION_HEIGHT) * (CHUNK_WIDTH + 2) * (CHUNK_WIDTH + 2) + (pos.z + 1) * (CHUNK_WIDTH + 2) + pos.x + 1);


#if PROTOCOL_VERSION < 347
        block->ChangeBlockstate(id, metadata, model_id, &pos);
#else
        block->ChangeBlockstate(id, model_id, &pos);
#endif

#if USE_GUI
        modified_since_last_rendered = true;
#endif
    }

    void Chunk::SetBlock(const Position& pos, const Block* block)
    {
        if (block == nullptr)
        {
#if PROTOCOL_VERSION < 347
            SetBlock(pos, 0, 0, -1);
#else
            SetBlock(pos, 0, -1);
#endif
        }
        else
        {
#if PROTOCOL_VERSION < 347
            SetBlock(pos, block->GetBlockstate()->GetId(), block->GetBlockstate()->GetMetadata(), block->GetModelId());
#else
            SetBlock(pos, block->GetBlockstate()->GetId(), block->GetModelId());
#endif
        }
    }
    const unsigned char Chunk::GetBlockLight(const Position &pos) const
    {
        if (pos.x < 0 || pos.x > CHUNK_WIDTH - 1 || pos.y < min_y || pos.y > height + min_y - 1 || pos.z < 0 || pos.z > CHUNK_WIDTH - 1)
        {
            return 0;
        }
        
        if (!sections[(pos.y - min_y) / SECTION_HEIGHT])
        {
            return 0;
        }

        return sections[(pos.y - min_y) / SECTION_HEIGHT]->block_light[((pos.y - min_y) % SECTION_HEIGHT) * CHUNK_WIDTH * CHUNK_WIDTH + pos.z * CHUNK_WIDTH + pos.x];
    }

    void Chunk::SetBlockLight(const Position &pos, const unsigned char v)
    {
        if (pos.x < 0 || pos.x > CHUNK_WIDTH - 1 || pos.y < min_y || pos.y > height + min_y - 1 || pos.z < 0 || pos.z > CHUNK_WIDTH - 1)
        {
            return;
        }

        if (!sections[(pos.y - min_y) / SECTION_HEIGHT])
        {
            AddSection((pos.y - min_y)/ SECTION_HEIGHT);
        }

        sections[(pos.y - min_y) / SECTION_HEIGHT]->block_light[((pos.y - min_y) % SECTION_HEIGHT) * CHUNK_WIDTH * CHUNK_WIDTH + pos.z * CHUNK_WIDTH + pos.x] = v;

        // Not necessary as we don't render lights
//#if USE_GUI
//        modified_since_last_rendered = true;
//#endif
    }

    const unsigned char Chunk::GetSkyLight(const Position &pos) const
    {
#if PROTOCOL_VERSION < 719
        if (dimension != Dimension::Overworld
#else
        if (dimension != "minecraft:overworld"
#endif
            || pos.x < 0 || pos.x > CHUNK_WIDTH - 1 || pos.y < min_y || pos.y > height + min_y - 1 || pos.z < 0 || pos.z > CHUNK_WIDTH - 1)
        {
            return 0;
        }

        if (!sections[(pos.y - min_y) / SECTION_HEIGHT])
        {
            return 0;
        }

        return sections[(pos.y - min_y) / SECTION_HEIGHT]->sky_light[((pos.y - min_y) % SECTION_HEIGHT) * CHUNK_WIDTH * CHUNK_WIDTH + pos.z * CHUNK_WIDTH + pos.x];
    }

    void Chunk::SetSkyLight(const Position &pos, const unsigned char v)
    {
#if PROTOCOL_VERSION < 719
        if (dimension != Dimension::Overworld
#else
        if (dimension != "minecraft:overworld"
#endif
            || pos.x < 0 || pos.x > CHUNK_WIDTH - 1 || pos.y < min_y || pos.y > height + min_y - 1 || pos.z < 0 || pos.z > CHUNK_WIDTH - 1)
        {
            return;
        }

        if (!sections[(pos.y - min_y) / SECTION_HEIGHT])
        {
            AddSection((pos.y - min_y) / SECTION_HEIGHT);
        }

        sections[(pos.y - min_y) / SECTION_HEIGHT]->block_light[((pos.y - min_y) % SECTION_HEIGHT) * CHUNK_WIDTH * CHUNK_WIDTH + pos.z * CHUNK_WIDTH + pos.x] = v;
        // Not necessary as we don't render lights
//#if USE_GUI
//        modified_since_last_rendered = true;
//#endif
    }

#if PROTOCOL_VERSION < 358
    const unsigned char Chunk::GetBiome(const int x, const int z) const
    {
        if (x < 0 || x > CHUNK_WIDTH - 1 || z < 0 || z > CHUNK_WIDTH - 1)
        {
            return 0;
        }

        return biomes[z * CHUNK_WIDTH + x];
    }

    void Chunk::SetBiome(const int x, const int z, const unsigned char b)
    {
        if (x < 0 || x > CHUNK_WIDTH - 1 || z < 0 || z > CHUNK_WIDTH - 1)
        {
            return;
        }

        biomes[z * CHUNK_WIDTH + x] = b;

#if USE_GUI
        modified_since_last_rendered = true;
#endif
    }

#elif PROTOCOL_VERSION < 552
    const int Chunk::GetBiome(const int x, const int z) const
    {
        if (x < 0 || x > CHUNK_WIDTH - 1 || z < 0 || z > CHUNK_WIDTH - 1)
        {
            return 0;
        }

        return biomes[z * CHUNK_WIDTH + x];
    }

    void Chunk::SetBiome(const int x, const int z, const int b)
    {
        if (x < 0 || x > CHUNK_WIDTH - 1 || z < 0 || z > CHUNK_WIDTH - 1)
        {
            return;
        }

        biomes[z * CHUNK_WIDTH + x] = b;

#if USE_GUI
        modified_since_last_rendered = true;
#endif
    }
#else
    const int Chunk::GetBiome(const int x, const int y, const int z) const
    {
        // y / 4 * 16 + z / 4 * 4 + x / 4
        return GetBiome((((y - min_y) >> 2) & 63) << 4 | ((z >> 2) & 3) << 2 | ((x >> 2) & 3));
    }

    const int Chunk::GetBiome(const int i) const
    {
        if (i < 0 || i > biomes.size() - 1)
        {
            return 0;
        }

        return biomes[i];
    }

    void Chunk::SetBiomes(const std::vector<int>& new_biomes)
    {
        if (new_biomes.size() != 64 * height / SECTION_HEIGHT)
        {
            LOG_ERROR("Trying to set biomes with a wrong size");
            return;
        }
        biomes = new_biomes;

#if USE_GUI
        modified_since_last_rendered = true;
#endif
    }

    void Chunk::SetBiome(const int x, const int y, const int z, const int new_biome)
    {
        // y / 4 * 16 + z / 4 * 4 + x / 4
        SetBiome((((y - min_y) >> 2) & 63) << 4 | ((z >> 2) & 3) << 2 | ((x >> 2) & 3), new_biome);
    }

    void Chunk::SetBiome(const int i, const int new_biome)
    {
        if (i < 0 || i > biomes.size() - 1)
        {
            return;
        }

        biomes[i] = new_biome;

#if USE_GUI
        modified_since_last_rendered = true;
#endif
    }
#endif

    void Chunk::UpdateNeighbour(const std::shared_ptr<Chunk> neighbour, const Orientation direction)
    {
        Position this_dest_position = Position(0, 0, 0);
        Position this_src_position = Position(0, 0, 0);
        Position neighbour_dest_position = Position(0, 0, 0);
        Position neighbour_src_position = Position(0, 0, 0);
        switch (direction)
        {
            // The neighbour is on "the left" on the x axis
        case Orientation::West:
            this_dest_position.x = -1;
            this_src_position.x = 0;
            neighbour_src_position.x = CHUNK_WIDTH - 1;
            neighbour_dest_position.x = CHUNK_WIDTH;

            for (int y = min_y; y < height + min_y; ++y)
            {
                this_dest_position.y = y;
                this_src_position.y = y;
                neighbour_src_position.y = y;
                neighbour_dest_position.y = y;
                for (int z = 0; z < CHUNK_WIDTH; ++z)
                {
                    this_dest_position.z = z;
                    this_src_position.z = z;
                    neighbour_src_position.z = z;
                    neighbour_dest_position.z = z;
                    // If the neighbour chunk is not loaded, just add air instead
                    if (neighbour == nullptr)
                    {
                        SetBlock(this_dest_position, nullptr);
                    }
                    // Otherwise, get the blocks and set this chunk's blocks
                    // on the neighbour
                    else
                    {
                        SetBlock(this_dest_position, neighbour->GetBlock(neighbour_src_position));
                        neighbour->SetBlock(neighbour_dest_position, GetBlock(this_src_position));
                    }
                }
            }
            break;
            // The neighbour is on "the right" on the x axis
        case Orientation::East:
            this_dest_position.x = CHUNK_WIDTH;
            this_src_position.x = CHUNK_WIDTH - 1;
            neighbour_src_position.x = 0;
            neighbour_dest_position.x = -1;

            for (int y = min_y; y < height + min_y; ++y)
            {
                this_dest_position.y = y;
                this_src_position.y = y;
                neighbour_src_position.y = y;
                neighbour_dest_position.y = y;
                for (int z = 0; z < CHUNK_WIDTH; ++z)
                {
                    this_dest_position.z = z;
                    this_src_position.z = z;
                    neighbour_src_position.z = z;
                    neighbour_dest_position.z = z;
                    // If the neighbour chunk is not loaded, just add air instead
                    if (neighbour == nullptr)
                    {
                        SetBlock(this_dest_position, nullptr);
                    }
                    // Otherwise, get the blocks and set this chunk's blocks
                    // on the neighbour
                    else
                    {
                        SetBlock(this_dest_position, neighbour->GetBlock(neighbour_src_position));
                        neighbour->SetBlock(neighbour_dest_position, GetBlock(this_src_position));
                    }
                }
            }
            break;
            // The neighbour is on "the left" on the z axis
        case Orientation::North:
            this_dest_position.z = -1;
            this_src_position.z = 0;
            neighbour_src_position.z = CHUNK_WIDTH - 1;
            neighbour_dest_position.z = CHUNK_WIDTH;

            for (int y = min_y; y < height + min_y; ++y)
            {
                this_dest_position.y = y;
                this_src_position.y = y;
                neighbour_src_position.y = y;
                neighbour_dest_position.y = y;
                for (int x = 0; x < CHUNK_WIDTH; ++x)
                {
                    this_dest_position.x = x;
                    this_src_position.x = x;
                    neighbour_src_position.x = x;
                    neighbour_dest_position.x = x;
                    // If the neighbour chunk is not loaded, just add air instead
                    if (neighbour == nullptr)
                    {
                        SetBlock(this_dest_position, nullptr);
                    }
                    // Otherwise, get the blocks and set this chunk's blocks
                    // on the neighbour
                    else
                    {
                        SetBlock(this_dest_position, neighbour->GetBlock(neighbour_src_position));
                        neighbour->SetBlock(neighbour_dest_position, GetBlock(this_src_position));
                    }
                }
            }
            break;
            // The neighbour is on "the right" on the z axis
        case Orientation::South:
            this_dest_position.z = CHUNK_WIDTH;
            this_src_position.z = CHUNK_WIDTH - 1;
            neighbour_src_position.z = 0;
            neighbour_dest_position.z = -1;

            for (int y = min_y; y < height + min_y; ++y)
            {
                this_dest_position.y = y;
                this_src_position.y = y;
                neighbour_src_position.y = y;
                neighbour_dest_position.y = y;
                for (int x = 0; x < CHUNK_WIDTH; ++x)
                {
                    this_dest_position.x = x;
                    this_src_position.x = x;
                    neighbour_src_position.x = x;
                    neighbour_dest_position.x = x;
                    // If the neighbour chunk is not loaded, just add air instead
                    if (neighbour == nullptr)
                    {
                        SetBlock(this_dest_position, nullptr);
                    }
                    // Otherwise, get the blocks and set this chunk's blocks
                    // on the neighbour
                    else
                    {
                        SetBlock(this_dest_position, neighbour->GetBlock(neighbour_src_position));
                        neighbour->SetBlock(neighbour_dest_position, GetBlock(this_src_position));
                    }
                }
            }
            break;
        default:
            break;
        }
    }

#if PROTOCOL_VERSION < 719
    const Dimension Chunk::GetDimension() const
#else
    const std::string& Chunk::GetDimension() const
#endif
    {
        return dimension;
    }

    const std::map<Position, std::shared_ptr<NBT::Value> >& Chunk::GetBlockEntitiesData() const
    {
        return block_entities_data;
    }

    const bool Chunk::HasSection(const int y) const
    {
        return sections[y] != nullptr;
    }

    void Chunk::AddSection(const int y)
    {
#if PROTOCOL_VERSION < 719
        sections[y] = std::shared_ptr<Section>(new Section(dimension == Dimension::Overworld));
#else
        sections[y] = std::shared_ptr<Section>(new Section(dimension == "minecraft:overworld"));
#endif
    }

} //Botcraft