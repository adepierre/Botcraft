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

#if PROTOCOL_VERSION < 755
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
#else
        void SetSkyYMask(const std::vector<unsigned long long int>& sky_Y_mask_)
        {
            sky_Y_mask = sky_Y_mask_;
        }

        void SetBlockYMask(const std::vector<unsigned long long int>& block_Y_mask_)
        {
            block_Y_mask = block_Y_mask_;
        }

        void SetEmptySkyYMask(const std::vector<unsigned long long int>& empty_sky_Y_mask_)
        {
            empty_sky_Y_mask = empty_sky_Y_mask_;
        }

        void SetEmptyBlockYMask(const std::vector<unsigned long long int>& empty_block_Y_mask_)
        {
            empty_block_Y_mask = empty_block_Y_mask_;
        }
#endif

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

#if PROTOCOL_VERSION < 755
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
#else
        const std::vector<unsigned long long int>& GetSkyYMask() const
        {
            return sky_Y_mask;
        }

        const std::vector<unsigned long long int>& GetBlockYMask() const
        {
            return block_Y_mask;
        }

        const std::vector<unsigned long long int>& GetEmptySkyYMask() const
        {
            return empty_sky_Y_mask;
        }

        const std::vector<unsigned long long int>& GetEmptyBlockYMask() const
        {
            return empty_block_Y_mask;
        }

#endif

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
#if PROTOCOL_VERSION < 755
            sky_Y_mask = ReadVarInt(iter, length);
            block_Y_mask = ReadVarInt(iter, length);
            empty_sky_Y_mask = ReadVarInt(iter, length);
            empty_block_Y_mask = ReadVarInt(iter, length);
#else
            const int sky_Y_mask_size = ReadVarInt(iter, length);
            sky_Y_mask = std::vector<unsigned long long int>(sky_Y_mask_size);
            for (int i = 0; i < sky_Y_mask_size; ++i)
            {
                sky_Y_mask[i] = ReadData<unsigned long long int>(iter, length);
            }
            const int block_Y_mask_size = ReadVarInt(iter, length);
            block_Y_mask = std::vector<unsigned long long int>(block_Y_mask_size);
            for (int i = 0; i < block_Y_mask_size; ++i)
            {
                block_Y_mask[i] = ReadData<unsigned long long int>(iter, length);
            }
            const int empty_sky_Y_mask_size = ReadVarInt(iter, length);
            empty_sky_Y_mask = std::vector<unsigned long long int>(empty_sky_Y_mask_size);
            for (int i = 0; i < empty_sky_Y_mask_size; ++i)
            {
                empty_sky_Y_mask[i] = ReadData<unsigned long long int>(iter, length);
            }
            const int empty_block_Y_mask_size = ReadVarInt(iter, length);
            empty_block_Y_mask = std::vector<unsigned long long int>(empty_block_Y_mask_size);
            for (int i = 0; i < empty_block_Y_mask_size; ++i)
            {
                empty_block_Y_mask[i] = ReadData<unsigned long long int>(iter, length);
            }
#endif

#if PROTOCOL_VERSION < 755
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
#else
            const int sky_light_arrays_size = ReadVarInt(iter, length);
            sky_light_arrays = std::vector<std::vector<char> >(sky_light_arrays_size);
            for (int i = 0; i < sky_light_arrays_size; ++i)
            {
                const int array_length = ReadVarInt(iter, length); // Should be 2048
                sky_light_arrays[i] = ReadArrayData<char>(iter, length, 2048);
            }

            const int block_light_arrays_size = ReadVarInt(iter, length);
            block_light_arrays = std::vector<std::vector<char> >(block_light_arrays_size);
            for (int i = 0; i < block_light_arrays_size; ++i)
            {
                const int array_length = ReadVarInt(iter, length); // Should be 2048
                block_light_arrays[i] = ReadArrayData<char>(iter, length, 2048);
            }
#endif
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
            WriteVarInt(x, container);
            WriteVarInt(z, container);
#if PROTOCOL_VERSION > 722
            WriteData<bool>(trust_edges, container);
#endif
#if PROTOCOL_VERSION < 755
            WriteVarInt(sky_Y_mask, container);
            WriteVarInt(block_Y_mask, container);
            WriteVarInt(empty_sky_Y_mask, container);
            WriteVarInt(empty_block_Y_mask, container);
#else
            WriteVarInt(sky_Y_mask.size(), container);
            for (int i = 0; i < sky_Y_mask.size(); ++i)
            {
                 WriteData<unsigned long long int>(sky_Y_mask[i], container);
            }
            WriteVarInt(block_Y_mask.size(), container);
            for (int i = 0; i < block_Y_mask.size(); ++i)
            {
                WriteData<unsigned long long int>(block_Y_mask[i], container);
            }
            WriteVarInt(empty_sky_Y_mask.size(), container);
            for (int i = 0; i < empty_sky_Y_mask.size(); ++i)
            {
                WriteData<unsigned long long int>(empty_sky_Y_mask[i], container);
            }
            WriteVarInt(empty_block_Y_mask.size(), container);
            for (int i = 0; i < empty_block_Y_mask.size(); ++i)
            {
                WriteData<unsigned long long int>(empty_block_Y_mask[i], container);
            }
#endif

#if PROTOCOL_VERSION > 754
            WriteVarInt(sky_light_arrays.size(), container);
#endif
            for (int i = 0; i < sky_light_arrays.size(); ++i)
            {
                WriteVarInt(sky_light_arrays[i].size(), container);
                WriteArrayData(sky_light_arrays[i], container);
            }

#if PROTOCOL_VERSION > 754
            WriteVarInt(block_light_arrays.size(), container);
#endif
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
#if PROTOCOL_VERSION < 755
            object["sky_Y_mask"] = picojson::value((double)sky_Y_mask);
            object["block_Y_mask"] = picojson::value((double)block_Y_mask);
            object["empty_sky_Y_mask"] = picojson::value((double)empty_sky_Y_mask);
            object["empty_block_Y_mask"] = picojson::value((double)empty_block_Y_mask);
#else
            object["sky_Y_mask"] = picojson::value("Vector of " + std::to_string(sky_Y_mask.size()) + " unsigned long long int");
            object["block_Y_mask"] = picojson::value("Vector of " + std::to_string(block_Y_mask.size()) + " unsigned long long int");
            object["empty_sky_Y_mask"] = picojson::value("Vector of " + std::to_string(empty_sky_Y_mask.size()) + " unsigned long long int");
            object["empty_block_Y_mask"] = picojson::value("Vector of " + std::to_string(empty_block_Y_mask.size()) + " unsigned long long int");
#endif

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
#if PROTOCOL_VERSION < 755
        int sky_Y_mask;
        int block_Y_mask;
        int empty_sky_Y_mask;
        int empty_block_Y_mask;
#else
        std::vector<unsigned long long int> sky_Y_mask;
        std::vector<unsigned long long int> block_Y_mask;
        std::vector<unsigned long long int> empty_sky_Y_mask;
        std::vector<unsigned long long int> empty_block_Y_mask;
#endif
        std::vector<std::vector<char> > sky_light_arrays;
        std::vector<std::vector<char> > block_light_arrays;
#if PROTOCOL_VERSION > 722
        bool trust_edges;
#endif
    };
} //ProtocolCraft

#endif