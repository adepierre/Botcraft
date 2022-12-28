#pragma once

#include "protocolCraft/BaseMessage.hpp"

#include <map>

namespace ProtocolCraft
{
    class ClientboundAwardStatsPacket : public BaseMessage<ClientboundAwardStatsPacket>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 340 // 1.12.2
            return 0x07;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
            return 0x07;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
            return 0x07;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
            return 0x07;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16 or 1.16.1
            return 0x06;
#elif PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 || PROTOCOL_VERSION == 754 // 1.16.2, 1.16.3, 1.16.4, 1.16.5
            return 0x06;
#elif PROTOCOL_VERSION == 755 || PROTOCOL_VERSION == 756 // 1.17.X
            return 0x07;
#elif PROTOCOL_VERSION == 757 || PROTOCOL_VERSION == 758 // 1.18, 1.18.1 or 1.18.2
            return 0x07;
#elif PROTOCOL_VERSION == 759 // 1.19
            return 0x04;
#elif PROTOCOL_VERSION == 760 // 1.19.1 or 1.19.2
            return 0x04;
#elif PROTOCOL_VERSION == 761 // 1.19.3
            return 0x04;
#else
#error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Award Stats";
        }

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
            int count = ReadData<VarInt>(iter, length);
            stats.clear();
            for (int i = 0; i < count; ++i)
            {
#if PROTOCOL_VERSION < 346
                std::string name = ReadData<std::string>(iter, length);
                int value = ReadData<VarInt>(iter, length);
                stats[name] = value;
#else
                int category_id = ReadData<VarInt>(iter, length);
                int stats_id = ReadData<VarInt>(iter, length);
                int value = ReadData<VarInt>(iter, length);

                stats[std::make_pair(category_id, stats_id)] = value;
#endif
            }
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<VarInt>(static_cast<int>(stats.size()), container);
            for (auto it = stats.begin(); it != stats.end(); ++it)
            {
#if PROTOCOL_VERSION < 346
                WriteData<std::string>(it->first, container);
#else
                WriteData<VarInt>(it->first.first, container);
                WriteData<VarInt>(it->first.second, container);
#endif
                WriteData<VarInt>(it->second, container);
            }
        }

        virtual const nlohmann::json SerializeImpl() const override
        {
            nlohmann::json output;

            output["stats"] = nlohmann::json::array();

            for (auto it = stats.begin(); it != stats.end(); it++)
            {
                nlohmann::json s;


#if PROTOCOL_VERSION < 346
                s["name"] = it->first;
#else
                s["category_id"] = it->first.first;
                s["stats_id"] = it->first.second;
#endif
                s["value"] = it->second;
                output.push_back(s);
            }

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