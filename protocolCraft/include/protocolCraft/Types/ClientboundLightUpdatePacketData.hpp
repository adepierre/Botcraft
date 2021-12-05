#pragma once

#if PROTOCOL_VERSION > 756
#include "protocolCraft/NetworkType.hpp"

namespace ProtocolCraft
{
    class ClientboundLightUpdatePacketData : public NetworkType
    {
    public:
        virtual ~ClientboundLightUpdatePacketData() override
        {

        }

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

        void SetSkyUpdates(std::vector<std::vector<char> >& sky_updates_)
        {
            sky_updates = sky_updates_;
        }

        void SetBlockUpdates(std::vector<std::vector<char> >& block_updates_)
        {
            block_updates = block_updates_;
        }

        void SetTrustEdges(const bool trust_edges_)
        {
            trust_edges = trust_edges_;
        }


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

        const std::vector<std::vector<char> >& GetSkyUpdates() const
        {
            return sky_updates;
        }

        const std::vector<std::vector<char> >& GetBlockUpdates() const
        {
            return block_updates;
        }

        const bool GetTrustEdges() const
        {
            return trust_edges;
        }

    protected:
        virtual void ReadImpl(ReadIterator &iter, size_t &length) override
        {
            trust_edges = ReadData<bool>(iter, length);
            
            const int sky_Y_mask_size = ReadData<VarInt>(iter, length);
            sky_Y_mask = std::vector<unsigned long long int>(sky_Y_mask_size);
            for (int i = 0; i < sky_Y_mask_size; ++i)
            {
                sky_Y_mask[i] = ReadData<unsigned long long int>(iter, length);
            }
            const int block_Y_mask_size = ReadData<VarInt>(iter, length);
            block_Y_mask = std::vector<unsigned long long int>(block_Y_mask_size);
            for (int i = 0; i < block_Y_mask_size; ++i)
            {
                block_Y_mask[i] = ReadData<unsigned long long int>(iter, length);
            }
            const int empty_sky_Y_mask_size = ReadData<VarInt>(iter, length);
            empty_sky_Y_mask = std::vector<unsigned long long int>(empty_sky_Y_mask_size);
            for (int i = 0; i < empty_sky_Y_mask_size; ++i)
            {
                empty_sky_Y_mask[i] = ReadData<unsigned long long int>(iter, length);
            }
            const int empty_block_Y_mask_size = ReadData<VarInt>(iter, length);
            empty_block_Y_mask = std::vector<unsigned long long int>(empty_block_Y_mask_size);
            for (int i = 0; i < empty_block_Y_mask_size; ++i)
            {
                empty_block_Y_mask[i] = ReadData<unsigned long long int>(iter, length);
            }

            const int sky_updates_size = ReadData<VarInt>(iter, length);
            sky_updates = std::vector<std::vector<char> >(sky_updates_size);
            for (int i = 0; i < sky_updates_size; ++i)
            {
                const int array_length = ReadData<VarInt>(iter, length); // Should be 2048
                sky_updates[i] = ReadArrayData<char>(iter, length, 2048);
            }

            const int block_updates_size = ReadData<VarInt>(iter, length);
            block_updates = std::vector<std::vector<char> >(block_updates_size);
            for (int i = 0; i < block_updates_size; ++i)
            {
                const int array_length = ReadData<VarInt>(iter, length); // Should be 2048
                block_updates[i] = ReadArrayData<char>(iter, length, 2048);
            }
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
            WriteData<bool>(trust_edges, container);

            WriteData<VarInt>(sky_Y_mask.size(), container);
            for (int i = 0; i < sky_Y_mask.size(); ++i)
            {
                WriteData<unsigned long long int>(sky_Y_mask[i], container);
            }
            WriteData<VarInt>(block_Y_mask.size(), container);
            for (int i = 0; i < block_Y_mask.size(); ++i)
            {
                WriteData<unsigned long long int>(block_Y_mask[i], container);
            }
            WriteData<VarInt>(empty_sky_Y_mask.size(), container);
            for (int i = 0; i < empty_sky_Y_mask.size(); ++i)
            {
                WriteData<unsigned long long int>(empty_sky_Y_mask[i], container);
            }
            WriteData<VarInt>(empty_block_Y_mask.size(), container);
            for (int i = 0; i < empty_block_Y_mask.size(); ++i)
            {
                WriteData<unsigned long long int>(empty_block_Y_mask[i], container);
            }

            WriteData<VarInt>(sky_updates.size(), container);
            for (int i = 0; i < sky_updates.size(); ++i)
            {
                WriteData<VarInt>(sky_updates[i].size(), container);
                WriteArrayData(sky_updates[i], container);
            }

            WriteData<VarInt>(block_updates.size(), container);
            for (int i = 0; i < block_updates.size(); ++i)
            {
                WriteData<VarInt>(block_updates[i].size(), container);
                WriteArrayData(block_updates[i], container);
            }
        }

        virtual const nlohmann::json SerializeImpl() const override
        {
            nlohmann::json output;

            output["trust_edges"] = trust_edges;

            output["sky_Y_mask"] = sky_Y_mask;
            output["block_Y_mask"] = block_Y_mask;
            output["empty_sky_Y_mask"] = empty_sky_Y_mask;
            output["empty_block_Y_mask"] = empty_block_Y_mask;

            output["sky_updates"] = nlohmann::json::array();
            for (int i = 0; i < sky_updates.size(); ++i)
            {
                output["sky_updates"].push_back(sky_updates[i]);
            }

            output["block_updates"] = nlohmann::json::array();
            for (int i = 0; i < block_updates.size(); ++i)
            {
                output["block_updates"].push_back(block_updates[i]);
            }


            return output;
        }

    private:
        std::vector<unsigned long long int> sky_Y_mask;
        std::vector<unsigned long long int> block_Y_mask;
        std::vector<unsigned long long int> empty_sky_Y_mask;
        std::vector<unsigned long long int> empty_block_Y_mask;

        std::vector<std::vector<char> > sky_updates;
        std::vector<std::vector<char> > block_updates;

        bool trust_edges;
    };
}
#endif
