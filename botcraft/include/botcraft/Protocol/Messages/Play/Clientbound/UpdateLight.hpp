#pragma once

#include <iostream>

#include "botcraft/Protocol/BaseMessage.hpp"
#include "botcraft/Game/Enums.hpp"

#include "botcraft/Version.hpp"

#if PROTOCOL_VERSION > 404 
namespace Botcraft
{
    class UpdateLight : public BaseMessage<UpdateLight>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
            return 0x24;
#else
#error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Update Light";
        }

        const int GetChunkX() const
        {
            return chunk_x;
        }

        const int GetChunkZ() const
        {
            return chunk_z;
        }

        const int GetSkyLightMask() const
        {
            return sky_light_mask;
        }

        const int GetBlockLightMask() const
        {
            return block_light_mask;
        }

        const int GetEmptySkyLightMask() const
        {
            return empty_sky_light_mask;
        }

        const int GetEmptyBlockLightMask() const
        {
            return empty_block_light_mask;
        }

        const std::vector<std::vector<char> >& GetSkyLightArrays() const
        {
            return sky_light_arrays;
        }

        const std::vector<std::vector<char> >& GetBlockLightArrays() const
        {
            return block_light_arrays;
        }

    protected:
        virtual void ReadImpl(ReadIterator &iter, size_t &length) override
        {
            chunk_x = ReadVarInt(iter, length);
            chunk_z = ReadVarInt(iter, length);
            sky_light_mask = ReadVarInt(iter, length);
            block_light_mask = ReadVarInt(iter, length);
            empty_sky_light_mask = ReadVarInt(iter, length);
            empty_block_light_mask = ReadVarInt(iter, length);

            sky_light_arrays.clear();
            for (int i = 0; i < 18; ++i)
            {
                if ((sky_light_mask >> i) & 1)
                {
                    const int array_length = ReadVarInt(iter, length); // Should be 2048
                    sky_light_arrays.push_back(ReadArrayData<char>(iter, length, array_length));
                }
            }

            block_light_arrays.clear();
            for (int i = 0; i < 18; ++i)
            {
                if ((block_light_mask >> i) & 1)
                {
                    const int array_length = ReadVarInt(iter, length); // Should be 2048
                    block_light_arrays.push_back(ReadArrayData<char>(iter, length, array_length));
                }
            }
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
            std::cerr << "Clientbound message" << std::endl;
        }

    private:
        int chunk_x;
        int chunk_z;
        int sky_light_mask;
        int block_light_mask;
        int empty_sky_light_mask;
        int empty_block_light_mask;
        std::vector<std::vector<char> > sky_light_arrays;
        std::vector<std::vector<char> > block_light_arrays;
    };
} //Botcraft

#endif