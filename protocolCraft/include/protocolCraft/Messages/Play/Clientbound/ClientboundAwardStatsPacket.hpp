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
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16.0 or 1.16.1
            return 0x06;
#elif PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 || PROTOCOL_VERSION == 754 // 1.16.2, 1.16.3, 1.16.4, 1.16.5
            return 0x06;
#elif PROTOCOL_VERSION == 755 || PROTOCOL_VERSION == 756 // 1.17.X
            return 0x07;
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
            int count = ReadVarInt(iter, length);
            stats.clear();
            for (int i = 0; i < count; ++i)
            {
#if PROTOCOL_VERSION < 346
                std::string name = ReadString(iter, length);
                int value = ReadVarInt(iter, length);
                stats[name] = value;
#else
                int category_id = ReadVarInt(iter, length);
                int stats_id = ReadVarInt(iter, length);
                int value = ReadVarInt(iter, length);

                stats[std::make_pair(category_id, stats_id)] = value;
#endif
            }
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteVarInt(stats.size(), container);
            for (auto it = stats.begin(); it != stats.end(); ++it)
            {
#if PROTOCOL_VERSION < 346
                WriteString(it->first, container);
#else
                WriteVarInt(it->first.first, container);
                WriteVarInt(it->first.second, container);
#endif
                WriteVarInt(it->second, container);
            }
        }

        virtual const picojson::value SerializeImpl() const override
        {
            picojson::value value(picojson::object_type, false);
            picojson::object& object = value.get<picojson::object>();

            object["stats"] = picojson::value(picojson::array_type, false);
            picojson::array& array = object["stats"].get<picojson::array>();
            for (auto it = stats.begin(); it != stats.end(); it++)
            {
                picojson::value value2(picojson::object_type, false);
                picojson::object& object2 = value2.get<picojson::object>();


#if PROTOCOL_VERSION < 346
                object2["name"] = picojson::value(it->first);
#else
                object2["category_id"] = picojson::value((double)it->first.first);
                object2["stats_id"] = picojson::value((double)it->first.second);
#endif
                object2["value"] = picojson::value((double)it->second);
                array.push_back(value2);
            }

            return value;
        }

    private:
#if PROTOCOL_VERSION < 346
        std::map<std::string, int> stats;
#else
        std::map<std::pair<int, int>, int> stats;
#endif

    };
} //ProtocolCraft