#pragma once

#include "protocolCraft/BaseMessage.hpp"
#if PROTOCOL_VERSION > 756 /* > 1.17.1 */
#include "protocolCraft/Types/ClientboundLightUpdatePacketData.hpp"
#endif

#if PROTOCOL_VERSION > 404 /* > 1.13.2 */
namespace ProtocolCraft
{
    class ClientboundLightUpdatePacket : public BaseMessage<ClientboundLightUpdatePacket>
    {
    public:
#if   PROTOCOL_VERSION == 477 /* 1.14 */ || PROTOCOL_VERSION == 480 /* 1.14.1 */ ||  \
      PROTOCOL_VERSION == 485 /* 1.14.2 */ || PROTOCOL_VERSION == 490 /* 1.14.3 */ ||  \
      PROTOCOL_VERSION == 498 /* 1.14.4 */
        static constexpr int packet_id = 0x24;
#elif PROTOCOL_VERSION == 573 /* 1.15 */ || PROTOCOL_VERSION == 575 /* 1.15.1 */ ||  \
      PROTOCOL_VERSION == 578 /* 1.15.2 */
        static constexpr int packet_id = 0x25;
#elif PROTOCOL_VERSION == 735 /* 1.16 */ || PROTOCOL_VERSION == 736 /* 1.16.1 */
        static constexpr int packet_id = 0x24;
#elif PROTOCOL_VERSION == 751 /* 1.16.2 */ || PROTOCOL_VERSION == 753 /* 1.16.3 */ ||  \
      PROTOCOL_VERSION == 754 /* 1.16.4/5 */
        static constexpr int packet_id = 0x23;
#elif PROTOCOL_VERSION == 755 /* 1.17 */ || PROTOCOL_VERSION == 756 /* 1.17.1 */ ||  \
      PROTOCOL_VERSION == 757 /* 1.18/.1 */ || PROTOCOL_VERSION == 758 /* 1.18.2 */
        static constexpr int packet_id = 0x25;
#elif PROTOCOL_VERSION == 759 /* 1.19 */
        static constexpr int packet_id = 0x22;
#elif PROTOCOL_VERSION == 760 /* 1.19.1/2 */
        static constexpr int packet_id = 0x24;
#elif PROTOCOL_VERSION == 761 /* 1.19.3 */
        static constexpr int packet_id = 0x23;
#elif PROTOCOL_VERSION == 762 /* 1.19.4 */ || PROTOCOL_VERSION == 763 /* 1.20/.1 */
        static constexpr int packet_id = 0x27;
#elif PROTOCOL_VERSION == 764 /* 1.20.2 */
        static constexpr int packet_id = 0x28;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Light Update";

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

#if PROTOCOL_VERSION < 757 /* < 1.18/.1 */
#if PROTOCOL_VERSION < 755 /* < 1.17 */
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

        void SetSkyUpdates(std::vector<std::vector<char> >& sky_updates_)
        {
            sky_updates = sky_updates_;
        }

        void SetBlockUpdates(std::vector<std::vector<char> >& block_updates_)
        {
            block_updates = block_updates_;
        }

#if PROTOCOL_VERSION > 722 /* > 1.15.2 */
        void SetTrustEdges(const bool trust_edges_)
        {
            trust_edges = trust_edges_;
        }
#endif
#else
        void SetLightData(const ClientboundLightUpdatePacketData& light_data_)
        {
            light_data = light_data_;
        }
#endif


        int GetX() const
        {
            return x;
        }

        int GetZ() const
        {
            return z;
        }

#if PROTOCOL_VERSION < 757 /* < 1.18/.1 */
#if PROTOCOL_VERSION < 755 /* < 1.17 */
        int GetSkyYMask() const
        {
            return sky_Y_mask;
        }

        int GetBlockYMask() const
        {
            return block_Y_mask;
        }

        int GetEmptySkyYMask() const
        {
            return empty_sky_Y_mask;
        }

        int GetEmptyBlockYMask() const
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

        const std::vector<std::vector<char> >& GetSkyUpdates() const
        {
            return sky_updates;
        }

        const std::vector<std::vector<char> >& GetBlockUpdates() const
        {
            return block_updates;
        }

#if PROTOCOL_VERSION > 722 /* > 1.15.2 */
        bool GetTrustEdges() const
        {
            return trust_edges;
        }
#endif
#else
        const ClientboundLightUpdatePacketData& GetLightData() const
        {
            return light_data;
        }
#endif

    protected:
        virtual void ReadImpl(ReadIterator &iter, size_t &length) override
        {
            x = ReadData<VarInt>(iter, length);
            z = ReadData<VarInt>(iter, length);
#if PROTOCOL_VERSION < 757 /* < 1.18/.1 */
#if PROTOCOL_VERSION > 722 /* > 1.15.2 */
            trust_edges = ReadData<bool>(iter, length);
#endif
#if PROTOCOL_VERSION < 755 /* < 1.17 */
            sky_Y_mask = ReadData<VarInt>(iter, length);
            block_Y_mask = ReadData<VarInt>(iter, length);
            empty_sky_Y_mask = ReadData<VarInt>(iter, length);
            empty_block_Y_mask = ReadData<VarInt>(iter, length);
#else
            sky_Y_mask = ReadVector<unsigned long long int>(iter, length);
            block_Y_mask = ReadVector<unsigned long long int>(iter, length);
            empty_sky_Y_mask = ReadVector<unsigned long long int>(iter, length);
            empty_block_Y_mask = ReadVector<unsigned long long int>(iter, length);
#endif

#if PROTOCOL_VERSION < 755 /* < 1.17 */
            sky_updates.clear();
            for (int i = 0; i < 18; ++i)
            {
                if ((sky_Y_mask >> i) & 1)
                {
                    sky_updates.push_back(ReadVector<char>(iter, length)); // Should always contain 2048 chars
                }
            }

            block_updates.clear();
            for (int i = 0; i < 18; ++i)
            {
                if ((block_Y_mask >> i) & 1)
                {
                    block_updates.push_back(ReadVector<char>(iter, length)); // Should always contain 2048 chars
                }
            }
#else
            sky_updates = ReadVector<std::vector<char>>(iter, length,
                [](ReadIterator& i, size_t& l)
                {
                    return ReadVector<char>(i, l); // Should always contain 2048 chars
                }
            );
            block_updates = ReadVector<std::vector<char>>(iter, length,
                [](ReadIterator& i, size_t& l)
                {
                    return ReadVector<char>(i, l); // Should always contain 2048 chars
                }
            );
#endif
#else
            light_data = ReadData<ClientboundLightUpdatePacketData>(iter, length);
#endif
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
            WriteData<VarInt>(x, container);
            WriteData<VarInt>(z, container);
#if PROTOCOL_VERSION < 757 /* < 1.18/.1 */
#if PROTOCOL_VERSION > 722 /* > 1.15.2 */
            WriteData<bool>(trust_edges, container);
#endif
#if PROTOCOL_VERSION < 755 /* < 1.17 */
            WriteData<VarInt>(sky_Y_mask, container);
            WriteData<VarInt>(block_Y_mask, container);
            WriteData<VarInt>(empty_sky_Y_mask, container);
            WriteData<VarInt>(empty_block_Y_mask, container);
#else
            WriteVector<unsigned long long int>(sky_Y_mask, container);
            WriteVector<unsigned long long int>(block_Y_mask, container);
            WriteVector<unsigned long long int>(empty_sky_Y_mask, container);
            WriteVector<unsigned long long int>(empty_block_Y_mask, container);
#endif

#if PROTOCOL_VERSION < 755 /* < 1.17 */
            for (const auto& v : sky_updates)
            {
                WriteVector<char>(v, container);
            }
#else
            WriteVector<std::vector<char>>(sky_updates, container,
                [](const std::vector<char>& v, WriteContainer& c)
                {
                    WriteVector<char>(v, c);
                }
            );
#endif

#if PROTOCOL_VERSION < 755 /* < 1.17 */
            for (const auto& v : block_updates)
            {
                WriteVector<char>(v, container);
            }
#else
            WriteVector<std::vector<char>>(block_updates, container,
                [](const std::vector<char>& v, WriteContainer& c)
                {
                    WriteVector<char>(v, c);
                }
            );
#endif
#else
            WriteData<ClientboundLightUpdatePacketData>(light_data, container);
#endif
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["x"] = x;
            output["z"] = z;
#if PROTOCOL_VERSION < 757 /* < 1.18/.1 */
#if PROTOCOL_VERSION > 722 /* > 1.15.2 */
            output["trust_edges"] = trust_edges;
#endif
            output["sky_Y_mask"] = sky_Y_mask;
            output["block_Y_mask"] = block_Y_mask;
            output["empty_sky_Y_mask"] = empty_sky_Y_mask;
            output["empty_block_Y_mask"] = empty_block_Y_mask;
            output["sky_updates"] = sky_updates;
            output["block_updates"] = block_updates;
#else
            output["light_data"] = light_data;
#endif

            return output;
        }

    private:
        int x = 0;
        int z = 0;
#if PROTOCOL_VERSION < 757 /* < 1.18/.1 */
#if PROTOCOL_VERSION < 755 /* < 1.17 */
        int sky_Y_mask = 0;
        int block_Y_mask = 0;
        int empty_sky_Y_mask = 0;
        int empty_block_Y_mask = 0;
#else
        std::vector<unsigned long long int> sky_Y_mask;
        std::vector<unsigned long long int> block_Y_mask;
        std::vector<unsigned long long int> empty_sky_Y_mask;
        std::vector<unsigned long long int> empty_block_Y_mask;
#endif
        std::vector<std::vector<char> > sky_updates;
        std::vector<std::vector<char> > block_updates;
#if PROTOCOL_VERSION > 722 /* > 1.15.2 */
        bool trust_edges = false;
#endif
#else
        ClientboundLightUpdatePacketData light_data;
#endif
    };
} //ProtocolCraft

#endif
