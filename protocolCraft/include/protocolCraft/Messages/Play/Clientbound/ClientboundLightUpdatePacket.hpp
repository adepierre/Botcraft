#pragma once

#include "protocolCraft/BaseMessage.hpp"

#if PROTOCOL_VERSION > 404
namespace ProtocolCraft
{
    class ClientboundLightUpdatePacket : public BaseMessage<ClientboundLightUpdatePacket>
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
#elif PROTOCOL_VERSION == 755 // 1.17
            return 0x25;
#else
#error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Light Update";
        }

        virtual ~ClientboundLightUpdatePacket() override
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

        void SetSkyYMask(const int sky_Y_mask_)
        {
            sky_Y_mask = sky_Y_mask_;
        }

        void SetBlockYMask(const int block_Y_mask_)
        {
            block_Y_mask = block_Y_mask_;
        }

        void SetEmptySkyYMask(const int empty_sky_Y_mask_)
        {
            empty_sky_Y_mask = empty_sky_Y_mask_;
        }

        void SetEmptyBlockYMask(const int empty_block_Y_mask_)
        {
            empty_block_Y_mask = empty_block_Y_mask_;
        }

        void SetSkyLightArrays(std::vector<std::vector<char> >& sky_light_arrays_)
        {
            sky_light_arrays = sky_light_arrays_;
        }

        void SetBlockLightArrays(std::vector<std::vector<char> >& block_light_arrays_)
        {
            block_light_arrays = block_light_arrays_;
        }

#if PROTOCOL_VERSION > 722
        void SetTrustEdges(const bool trust_edges_)
        {
            trust_edges = trust_edges_;
        }
#endif


        const int GetX() const
        {
            return x;
        }

        const int GetZ() const
        {
            return z;
        }

        const int GetSkyYMask() const
        {
            return sky_Y_mask;
        }

        const int GetBlockYMask() const
        {
            return block_Y_mask;
        }

        const int GetEmptySkyYMask() const
        {
            return empty_sky_Y_mask;
        }

        const int GetEmptyBlockYMask() const
        {
            return empty_block_Y_mask;
        }

        const std::vector<std::vector<char> >& GetSkyLightArrays() const
        {
            return sky_light_arrays;
        }

        const std::vector<std::vector<char> >& GetBlockLightArrays() const
        {
            return block_light_arrays;
        }

#if PROTOCOL_VERSION > 722
        const bool GetTrustEdges() const
        {
            return trust_edges;
        }
#endif

    protected:
        virtual void ReadImpl(ReadIterator &iter, size_t &length) override
        {
            x = ReadVarInt(iter, length);
            z = ReadVarInt(iter, length);
#if PROTOCOL_VERSION > 722
            trust_edges = ReadData<bool>(iter, length);
#endif
            sky_Y_mask = ReadVarInt(iter, length);
            block_Y_mask = ReadVarInt(iter, length);
            empty_sky_Y_mask = ReadVarInt(iter, length);
            empty_block_Y_mask = ReadVarInt(iter, length);

            sky_light_arrays.clear();
            for (int i = 0; i < 18; ++i)
            {
                if ((sky_Y_mask >> i) & 1)
                {
                    const int array_length = ReadVarInt(iter, length); // Should be 2048
                    sky_light_arrays.push_back(ReadArrayData<char>(iter, length, array_length));
                }
            }

            block_light_arrays.clear();
            for (int i = 0; i < 18; ++i)
            {
                if ((block_Y_mask >> i) & 1)
                {
                    const int array_length = ReadVarInt(iter, length); // Should be 2048
                    block_light_arrays.push_back(ReadArrayData<char>(iter, length, array_length));
                }
            }
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
            WriteVarInt(x, container);
            WriteVarInt(z, container);
#if PROTOCOL_VERSION > 722
            WriteData<bool>(trust_edges, container);
#endif
            WriteVarInt(sky_Y_mask, container);
            WriteVarInt(block_Y_mask, container);
            WriteVarInt(empty_sky_Y_mask, container);
            WriteVarInt(empty_block_Y_mask, container);

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

            object["x"] = picojson::value((double)x);
            object["z"] = picojson::value((double)z);
#if PROTOCOL_VERSION > 722
            object["trust_edges"] = picojson::value(trust_edges);
#endif
            object["sky_Y_mask"] = picojson::value((double)sky_Y_mask);
            object["block_Y_mask"] = picojson::value((double)block_Y_mask);
            object["empty_sky_Y_mask"] = picojson::value((double)empty_sky_Y_mask);
            object["empty_block_Y_mask"] = picojson::value((double)empty_block_Y_mask);

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
        int x;
        int z;
        int sky_Y_mask;
        int block_Y_mask;
        int empty_sky_Y_mask;
        int empty_block_Y_mask;
        std::vector<std::vector<char> > sky_light_arrays;
        std::vector<std::vector<char> > block_light_arrays;
#if PROTOCOL_VERSION > 722
        bool trust_edges;
#endif
    };
} //ProtocolCraft

#endif