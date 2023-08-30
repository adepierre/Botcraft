#pragma once

#include "protocolCraft/BaseMessage.hpp"

#include <map>

namespace ProtocolCraft
{
    class ClientboundAwardStatsPacket : public BaseMessage<ClientboundAwardStatsPacket>
    {
    public:
#if   PROTOCOL_VERSION == 340 || PROTOCOL_VERSION == 393 ||  \
      PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 ||  \
      PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 ||  \
      PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 ||  \
      PROTOCOL_VERSION == 498 || PROTOCOL_VERSION == 573 ||  \
      PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578
        static constexpr int packet_id = 0x07;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736 ||  \
      PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 ||  \
      PROTOCOL_VERSION == 754
        static constexpr int packet_id = 0x06;
#elif PROTOCOL_VERSION == 755 || PROTOCOL_VERSION == 756 ||  \
      PROTOCOL_VERSION == 757 || PROTOCOL_VERSION == 758
        static constexpr int packet_id = 0x07;
#elif PROTOCOL_VERSION == 759 || PROTOCOL_VERSION == 760 ||  \
      PROTOCOL_VERSION == 761
        static constexpr int packet_id = 0x04;
#elif PROTOCOL_VERSION == 762 || PROTOCOL_VERSION == 763
        static constexpr int packet_id = 0x05;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Award Stats";

        virtual ~ClientboundAwardStatsPacket() override
        {

        }

#if PROTOCOL_VERSION < 346
        void SetStats(const std::map<std::string, int>& stats_)
        {
            stats = stats_;
        }
#else
        void SetStats(const std::map<std::pair<int, int>, int>& stats_)
        {
            stats = stats_;
        }
#endif


#if PROTOCOL_VERSION < 346
        const std::map<std::string, int>& GetStats() const
        {
            return stats;
        }
#else
        const std::map<std::pair<int, int>, int>& GetStats() const
        {
            return stats;
        }
#endif


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {

#if PROTOCOL_VERSION < 346
            stats = ReadMap<std::string, int>(iter, length,
                [](ReadIterator& i, size_t& l)
                {
                    const std::string name = ReadData<std::string>(i, l);
                    const int val = ReadData<VarInt>(i, l);

                    return std::make_pair(name, val);
                }
            );
#else
            stats = ReadMap<std::pair<int, int>, int>(iter, length,
                [](ReadIterator& i, size_t& l)
                {
                    const int category_id = ReadData<VarInt>(i, l);
                    const int stats_id = ReadData<VarInt>(i, l);
                    const int val = ReadData<VarInt>(i, l);

                    return std::make_pair(std::make_pair(category_id, stats_id), val);
                }
            );
#endif
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
#if PROTOCOL_VERSION < 346
            WriteMap<std::string, int>(stats, container,
                [](const std::pair<const std::string, int>& p, WriteContainer& c)
                {
                    WriteData<std::string>(p.first, c);
                    WriteData<VarInt>(p.second, c);
                }
            );
#else
            WriteMap<std::pair<int, int>, int>(stats, container,
                [](const std::pair<const std::pair<int, int>, int>& p, WriteContainer& c)
                {
                    WriteData<VarInt>(p.first.first, c);
                    WriteData<VarInt>(p.first.second, c);
                    WriteData<VarInt>(p.second, c);
                }
            );
#endif
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

#if PROTOCOL_VERSION < 346
            output["stats"] = stats;
#else
            output["stats"] = Json::Array();
            for (const auto& p : stats)
            {
                output.push_back({
                    {"category_id", p.first.first},
                    {"stats_id", p.first.second},
                    {"value", p.second} }
                );
            }
#endif

            return output;
        }

    private:
#if PROTOCOL_VERSION < 346
        std::map<std::string, int> stats;
#else
        std::map<std::pair<int, int>, int> stats;
#endif

    };
} //ProtocolCraft
