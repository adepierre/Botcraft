#pragma once

#if PROTOCOL_VERSION > 756 /* > 1.17.1 */
#include "protocolCraft/NetworkType.hpp"

namespace ProtocolCraft
{
    class ClientboundLightUpdatePacketData : public NetworkType
    {
    public:
        virtual ~ClientboundLightUpdatePacketData() override
        {

        }


#if PROTOCOL_VERSION < 763 /* < 1.20/.1 */
        void SetTrustEdges(const bool trust_edges_)
        {
            trust_edges = trust_edges_;
        }
#endif

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


#if PROTOCOL_VERSION < 763 /* < 1.20/.1 */
        bool GetTrustEdges() const
        {
            return trust_edges;
        }
#endif

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
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
#if PROTOCOL_VERSION < 763 /* < 1.20/.1 */
            trust_edges = ReadData<bool>(iter, length);
#endif
            
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

        virtual void WriteImpl(WriteContainer& container) const override
        {
#if PROTOCOL_VERSION < 763 /* < 1.20/.1 */
            WriteData<bool>(trust_edges, container);
#endif

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

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

#if PROTOCOL_VERSION < 763 /* < 1.20/.1 */
            output["trust_edges"] = trust_edges;
#endif
            output["sky_Y_mask"] = sky_Y_mask;
            output["block_Y_mask"] = block_Y_mask;
            output["empty_sky_Y_mask"] = empty_sky_Y_mask;
            output["empty_block_Y_mask"] = empty_block_Y_mask;
            output["sky_updates"] = sky_updates;
            output["block_updates"] = block_updates;

            return output;
        }

    private:
#if PROTOCOL_VERSION < 763 /* < 1.20/.1 */
        bool trust_edges = false;
#endif

        std::vector<unsigned long long int> sky_Y_mask;
        std::vector<unsigned long long int> block_Y_mask;
        std::vector<unsigned long long int> empty_sky_Y_mask;
        std::vector<unsigned long long int> empty_block_Y_mask;

        std::vector<std::vector<char> > sky_updates;
        std::vector<std::vector<char> > block_updates;
    };
}
#endif
