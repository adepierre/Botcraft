#pragma once

#include "protocolCraft/BaseMessage.hpp"

#if PROTOCOL_VERSION > 404
namespace ProtocolCraft
{
    class UpdateLight : public BaseMessage<UpdateLight>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
            return 0x24;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
			return 0x25;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16.0 or 1.16.1
            return 0x24;
#elif PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 || PROTOCOL_VERSION == 754 // 1.16.2, 1.16.3, 1.16.4, 1.16.5
            return 0x23;
#else
#error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Update Light";
        }

        void SetChunkX(const int chunk_x_)
        {
            chunk_x = chunk_x_;
        }

        void SetChunkZ(const int chunk_z_)
        {
            chunk_z = chunk_z_;
        }

#if PROTOCOL_VERSION > 722
        void SetTrustEdges(const bool trust_edges_)
        {
            trust_edges = trust_edges_;
        }
#endif

        void SetSkyLightMask(const int sky_light_mask_)
        {
            sky_light_mask = sky_light_mask_;
        }

        void SetBlockLightMask(const int block_light_mask_)
        {
            block_light_mask = block_light_mask_;
        }

        void SetEmptySkyLightMask(const int empty_sky_light_mask_)
        {
            empty_sky_light_mask = empty_sky_light_mask_;
        }

        void SetEmptyBlockLightMask(const int empty_block_light_mask_)
        {
            empty_block_light_mask = empty_block_light_mask_;
        }

        void SetSkyLightArrays(std::vector<std::vector<char> >& sky_light_arrays_)
        {
            sky_light_arrays = sky_light_arrays_;
        }

        void SetBlockLightArrays(std::vector<std::vector<char> >& block_light_arrays_)
        {
            block_light_arrays = block_light_arrays_;
        }

        const int GetChunkX() const
        {
            return chunk_x;
        }

        const int GetChunkZ() const
        {
            return chunk_z;
        }

#if PROTOCOL_VERSION > 722
        const bool GetTrustEdges() const
        {
            return trust_edges;
        }
#endif

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
#if PROTOCOL_VERSION > 722
            trust_edges = ReadData<bool>(iter, length);
#endif
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
            WriteVarInt(chunk_x, container);
            WriteVarInt(chunk_z, container);
#if PROTOCOL_VERSION > 722
            WriteData<bool>(trust_edges, container);
#endif
            WriteVarInt(sky_light_mask, container);
            WriteVarInt(block_light_mask, container);
            WriteVarInt(empty_sky_light_mask, container);
            WriteVarInt(empty_block_light_mask, container);

            for (int i = 0; i < sky_light_arrays.size(); ++i)
            {
                WriteVarInt(sky_light_arrays[i].size(), container);
                WriteArrayData(sky_light_arrays[i], container);
            }

            for (int i = 0; i < block_light_arrays.size(); ++i)
            {
                WriteVarInt(block_light_arrays[i].size(), container);
                WriteArrayData(block_light_arrays[i], container);
            }
        }

        virtual const picojson::value SerializeImpl() const override
        {
            picojson::value value(picojson::object_type, false);
            picojson::object& object = value.get<picojson::object>();

            object["chunk_x"] = picojson::value((double)chunk_x);
            object["chunk_z"] = picojson::value((double)chunk_z);
#if PROTOCOL_VERSION > 722
            object["trust_edges"] = picojson::value(trust_edges);
#endif
            object["sky_light_mask"] = picojson::value((double)sky_light_mask);
            object["block_light_mask"] = picojson::value((double)block_light_mask);
            object["empty_sky_light_mask"] = picojson::value((double)empty_sky_light_mask);
            object["empty_block_light_mask"] = picojson::value((double)empty_block_light_mask);

            object["sky_light_arrays"] = picojson::value(picojson::array_type, false);

            picojson::array& array1 = object["sky_light_arrays"].get<picojson::array>();
            array1.reserve(sky_light_arrays.size());

            for (int i = 0; i < sky_light_arrays.size(); ++i)
            {
                array1.push_back(picojson::value("Vector of " + std::to_string(sky_light_arrays[i].size()) + " char"));
            }

            object["block_light_arrays"] = picojson::value(picojson::array_type, false);

            picojson::array& array2 = object["block_light_arrays"].get<picojson::array>();
            array2.reserve(block_light_arrays.size());

            for (int i = 0; i < block_light_arrays.size(); ++i)
            {
                array2.push_back(picojson::value("Vector of " + std::to_string(block_light_arrays[i].size()) + " char"));
            }

            return value;
        }

    private:
        int chunk_x;
        int chunk_z;
#if PROTOCOL_VERSION > 722
        bool trust_edges;
#endif
        int sky_light_mask;
        int block_light_mask;
        int empty_sky_light_mask;
        int empty_block_light_mask;
        std::vector<std::vector<char> > sky_light_arrays;
        std::vector<std::vector<char> > block_light_arrays;
    };
} //ProtocolCraft

#endif