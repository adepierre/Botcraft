#include "botcraft/Game/World/Chunk.hpp"
#include "botcraft/Game/World/Section.hpp"

#include "protocolCraft/Types/NBT/TagInt.hpp"

#include <iostream>

using namespace ProtocolCraft;

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

#if PROTOCOL_VERSION < 719
    Chunk::Chunk(const Dimension &dim)
#else
    Chunk::Chunk(const std::string& dim)
#endif
    {
        dimension = dim;
#if PROTOCOL_VERSION < 358
        biomes = std::vector<unsigned char>(CHUNK_WIDTH * CHUNK_WIDTH, 0);
#elif PROTOCOL_VERSION < 552
        biomes = std::vector<int>(CHUNK_WIDTH * CHUNK_WIDTH, 0);
#else
		biomes = std::vector<int>(BIOMES_SIZE, 0);
#endif
        sections = std::vector<std::shared_ptr<Section> >(CHUNK_HEIGHT / SECTION_HEIGHT);

#if USE_GUI
        modified_since_last_rendered = true;
#endif
    }

    Chunk::Chunk(const Chunk& c)
    {
        dimension = c.dimension;
#if PROTOCOL_VERSION < 358
        biomes = c.biomes;
#elif PROTOCOL_VERSION < 552
        biomes = c.biomes;
#else
        biomes = c.biomes;
#endif
        sections = std::vector<std::shared_ptr<Section> >(CHUNK_HEIGHT / SECTION_HEIGHT);
        for (int i = 0; i < c.sections.size(); i++)
        {
            if (c.sections[i] == nullptr)
            {
                sections[i] = nullptr;
            }
            else
            {
                sections[i] = std::shared_ptr<Section>(new Section(*c.sections[i]));
            }
        }

        for (auto it = c.block_entities_data.begin(); it != c.block_entities_data.end(); it++)
        {
            block_entities_data[it->first] = std::shared_ptr<NBT>(new NBT(*it->second));
        }
    }

    const Position Chunk::BlockCoordsToChunkCoords(const Position& pos)
    {
        return Position((int)floor(pos.x / (double)CHUNK_WIDTH), 0, (int)floor(pos.z / (double)CHUNK_WIDTH));
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

    void Chunk::LoadChunkData(const std::vector<unsigned char>& data, const int primary_bit_mask, const bool ground_up_continuous)
    {
        std::vector<unsigned char>::const_iterator iter = data.begin();
        size_t length = data.size();

        if (data.size() == 0)
        {
            std::cerr << "Error, cannot load chunk data without data" << std::endl;
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
                    std::cerr << "Error, bits per block must be between 4 and 8 when using a palette. Stop loading chunk data" << std::endl;
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
                    std::cerr << "Error, palette length should be 0 for global palette. Stop loading chunk data" << std::endl;
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
#if PROTOCOL_VERSION > 712
            int bit_offset = 0;
#endif
            for (int block_y = 0; block_y < SECTION_HEIGHT; ++block_y)
            {
                for (int block_z = 0; block_z < CHUNK_WIDTH; ++block_z)
                {
                    for (int block_x = 0; block_x < CHUNK_WIDTH; ++block_x)
                    {

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

                        SetBlock(Position(block_x, block_y + sectionY * SECTION_HEIGHT, block_z), id, metadata);
#else
                        SetBlock(Position(block_x, block_y + sectionY * SECTION_HEIGHT, block_z), raw_id);
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

                        SetBlockLight(Position(block_x, block_y + sectionY * SECTION_HEIGHT, block_z), two_light_values & 0x0F);
                        SetBlockLight(Position(block_x + 1, block_y + sectionY * SECTION_HEIGHT, block_z), (two_light_values >> 4) & 0x0F);
                    }
                }
            }

            //Sky light
            if (GetDimension() == Dimension::Overworld)
            {
                for (int block_y = 0; block_y < SECTION_HEIGHT; ++block_y)
                {
                    for (int block_z = 0; block_z < CHUNK_WIDTH; ++block_z)
                    {
                        for (int block_x = 0; block_x < CHUNK_WIDTH; block_x += 2)
                        {
                            unsigned char two_light_values = ReadData<unsigned char>(iter, length);

                            SetSkyLight(Position(block_x, block_y + sectionY * SECTION_HEIGHT, block_z), two_light_values & 0x0F);
                            SetSkyLight(Position(block_x + 1, block_y + sectionY * SECTION_HEIGHT, block_z), (two_light_values >> 4) & 0x0F);
                        }
                    }
                }
            }
#endif
        }

#if PROTOCOL_VERSION > 551
        SetBiomes(biomes);
#else
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

    void Chunk::LoadChunkBlockEntitiesData(const std::vector<unsigned char>& data, const int number_block_entities)
    {
        // Block entities data
        block_entities_data.clear();

        if (number_block_entities == 0)
        {
            return;
        }

        auto iter_entities = data.begin();
        size_t length_entitites_data = data.size();

        for (int i = 0; i < number_block_entities; ++i)
        {
            std::shared_ptr<NBT> current_nbt = std::shared_ptr<NBT>(new NBT);
            current_nbt->Read(iter_entities, length_entitites_data);

            if (current_nbt->HasData())
            {
                std::shared_ptr<TagInt> tag_x = std::dynamic_pointer_cast<TagInt>(current_nbt->GetTag("x"));
                std::shared_ptr<TagInt> tag_y = std::dynamic_pointer_cast<TagInt>(current_nbt->GetTag("y"));
                std::shared_ptr<TagInt> tag_z = std::dynamic_pointer_cast<TagInt>(current_nbt->GetTag("z"));

                if (tag_x && tag_y && tag_z)
                {
                    block_entities_data[Position(tag_x->GetValue(), tag_y->GetValue(), tag_z->GetValue())] = current_nbt;
                }
            }
        }

#if USE_GUI
        modified_since_last_rendered = true;
#endif
    }

    const Block *Chunk::GetBlock(const Position &pos) const
    {
        if (pos.x < -1 || pos.x > CHUNK_WIDTH || pos.y < 0 || pos.y > CHUNK_HEIGHT - 1 || pos.z < -1 || pos.z > CHUNK_WIDTH)
        {
            return nullptr;
        }

        if (!sections[pos.y / SECTION_HEIGHT])
        {
            return nullptr;
        }

        return sections[pos.y / SECTION_HEIGHT]->data_blocks.data() + ((pos.y % SECTION_HEIGHT) * (CHUNK_WIDTH + 2) * (CHUNK_WIDTH + 2) + (pos.z + 1) * (CHUNK_WIDTH + 2) + pos.x + 1);
    }

#if PROTOCOL_VERSION < 347
    void Chunk::SetBlock(const Position &pos, const unsigned int id, unsigned char metadata, const int model_id)
#else
    void Chunk::SetBlock(const Position &pos, const unsigned int id, const int model_id)
#endif
    {
        if (pos.x < -1 || pos.x > CHUNK_WIDTH || pos.y < 0 || pos.y > CHUNK_HEIGHT - 1 || pos.z < -1 || pos.z > CHUNK_WIDTH)
        {
            return;
        }

        if (!sections[pos.y / SECTION_HEIGHT])
        {
            if (id == 0)
            {
                return;
            }
            else
            {
                AddSection(pos.y / SECTION_HEIGHT);
            }
        }
        Block *block = sections[pos.y / SECTION_HEIGHT]->data_blocks.data() + ((pos.y % SECTION_HEIGHT) * (CHUNK_WIDTH + 2) * (CHUNK_WIDTH + 2) + (pos.z + 1) * (CHUNK_WIDTH + 2) + pos.x + 1);


#if PROTOCOL_VERSION < 347
        block->ChangeBlockstate(id, metadata, model_id);
#else
        block->ChangeBlockstate(id, model_id);
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
        if (pos.x < 0 || pos.x > CHUNK_WIDTH - 1 || pos.y < 0 || pos.y > CHUNK_HEIGHT - 1 || pos.z < 0 || pos.z > CHUNK_WIDTH - 1)
        {
            return 0;
        }
        
        if (!sections[pos.y / SECTION_HEIGHT])
        {
            return 0;
        }

        return sections[pos.y / SECTION_HEIGHT]->block_light[(pos.y % SECTION_HEIGHT) * CHUNK_WIDTH * CHUNK_WIDTH + pos.z * CHUNK_WIDTH + pos.x];
    }

    void Chunk::SetBlockLight(const Position &pos, const unsigned char v)
    {
        if (pos.x < 0 || pos.x > CHUNK_WIDTH - 1 || pos.y < 0 || pos.y > CHUNK_HEIGHT - 1 || pos.z < 0 || pos.z > CHUNK_WIDTH - 1)
        {
            return;
        }

        if (!sections[pos.y / SECTION_HEIGHT])
        {
            AddSection(pos.y / SECTION_HEIGHT);
        }

        sections[pos.y / SECTION_HEIGHT]->block_light[(pos.y % SECTION_HEIGHT) * CHUNK_WIDTH * CHUNK_WIDTH + pos.z * CHUNK_WIDTH + pos.x] = v;

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
            || pos.x < 0 || pos.x > CHUNK_WIDTH - 1 || pos.y < 0 || pos.y > CHUNK_HEIGHT - 1 || pos.z < 0 || pos.z > CHUNK_WIDTH - 1)
        {
            return 0;
        }

        if (!sections[pos.y / SECTION_HEIGHT])
        {
            return 0;
        }

        return sections[pos.y / SECTION_HEIGHT]->sky_light[(pos.y % SECTION_HEIGHT) * CHUNK_WIDTH * CHUNK_WIDTH + pos.z * CHUNK_WIDTH + pos.x];
    }

    void Chunk::SetSkyLight(const Position &pos, const unsigned char v)
    {
#if PROTOCOL_VERSION < 719
        if (dimension != Dimension::Overworld
#else
        if (dimension != "minecraft:overworld"
#endif
            || pos.x < 0 || pos.x > CHUNK_WIDTH - 1 || pos.y < 0 || pos.y > CHUNK_HEIGHT - 1 || pos.z < 0 || pos.z > CHUNK_WIDTH - 1)
        {
            return;
        }

        if (!sections[pos.y / SECTION_HEIGHT])
        {
            AddSection(pos.y / SECTION_HEIGHT);
        }

        sections[pos.y / SECTION_HEIGHT]->block_light[(pos.y % SECTION_HEIGHT) * CHUNK_WIDTH * CHUNK_WIDTH + pos.z * CHUNK_WIDTH + pos.x] = v;
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
		return GetBiome(((y >> 2) & 63) << 4 | ((z >> 2) & 3) << 2 | ((x >> 2) & 3));
	}

	const int Chunk::GetBiome(const int i) const
	{
		if (i < 0 || i > BIOMES_SIZE - 1)
		{
			return 0;
		}

		return biomes[i];
	}

	void Chunk::SetBiomes(const std::vector<int>& new_biomes)
	{
		if (new_biomes.size() != BIOMES_SIZE)
		{
			std::cerr << "Warning, trying to set biomes with a wrong size" << std::endl;
			return;
		}
		biomes = new_biomes;

#if USE_GUI
        modified_since_last_rendered = true;
#endif
	}

	void Chunk::SetBiome(const int x, const int y, const int z, const int new_biome)
	{
		SetBiome(((y >> 2) & 63) << 4 | ((z >> 2) & 3) << 2 | ((x >> 2) & 3), new_biome);
	}

	void Chunk::SetBiome(const int i, const int new_biome)
	{
		if (i < 0 || i > BIOMES_SIZE - 1)
		{
			return;
		}

		biomes[i] = new_biome;

#if USE_GUI
        modified_since_last_rendered = true;
#endif
	}
#endif

    std::shared_ptr<NBT> Chunk::GetBlockEntityData(const Position &pos)
    {
        auto it = block_entities_data.find(pos);
        if (it == block_entities_data.end())
        {
            return nullptr;
        }

        return it->second;
    }

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

            for (int y = 0; y < CHUNK_HEIGHT; ++y)
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

            for (int y = 0; y < CHUNK_HEIGHT; ++y)
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

            for (int y = 0; y < CHUNK_HEIGHT; ++y)
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

            for (int y = 0; y < CHUNK_HEIGHT; ++y)
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

    std::map<Position, std::shared_ptr<NBT> >& Chunk::GetBlockEntitiesData()
    {
        return block_entities_data;
    }

    const std::map<Position, std::shared_ptr<NBT> >& Chunk::GetBlockEntitiesData() const
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