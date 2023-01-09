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


        void SetTrustEdges(const bool trust_edges_)
        {
            trust_edges = trust_edges_;
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


        bool GetTrustEdges() const
        {
            return trust_edges;
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

    protected:
        virtual void ReadImpl(ReadIterator &iter, size_t &length) override
        {
            trust_edges = ReadData<bool>(iter, length);
            
            sky_Y_mask = ReadVector<unsigned long long int>(iter, length);
            block_Y_mask = ReadVector<unsigned long long int>(iter, length);
            empty_sky_Y_mask = ReadVector<unsigned long long int>(iter, length);
            empty_block_Y_mask = ReadVector<unsigned long long int>(iter, length);

            sky_updates = ReadVector<std::vector<char>>(iter, length,
                [](ReadIterator& i, size_t& l)
                {
                    return ReadVector<char>(i, l);
                }
            );

            block_updates = ReadVector<std::vector<char>>(iter, length,
                [](ReadIterator& i, size_t& l)
                {
                    return ReadVector<char>(i, l);
                }
            );
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
            WriteData<bool>(trust_edges, container);

            WriteVector<unsigned long long int>(sky_Y_mask, container);
            WriteVector<unsigned long long int>(block_Y_mask, container);
            WriteVector<unsigned long long int>(empty_sky_Y_mask, container);
            WriteVector<unsigned long long int>(empty_block_Y_mask, container);

            WriteVector<std::vector<char>>(sky_updates, container,
                [](const std::vector<char>& v, WriteContainer& c)
                {
                    WriteVector<char>(v, c);
                }
            );

            WriteVector<std::vector<char>>(block_updates, container,
                [](const std::vector<char>& v, WriteContainer& c)
                {
                    WriteVector<char>(v, c);
                }
            );
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
            for (const auto& v : sky_updates)
            {
                output["sky_updates"].push_back(v);
            }

            output["block_updates"] = nlohmann::json::array();
            for (const auto& v : block_updates)
            {
                output["block_updates"].push_back(v);
            }


            return output;
        }

    private:
        bool trust_edges;

        std::vector<unsigned long long int> sky_Y_mask;
        std::vector<unsigned long long int> block_Y_mask;
        std::vector<unsigned long long int> empty_sky_Y_mask;
        std::vector<unsigned long long int> empty_block_Y_mask;

        std::vector<std::vector<char> > sky_updates;
        std::vector<std::vector<char> > block_updates;
    };
}
#endif
