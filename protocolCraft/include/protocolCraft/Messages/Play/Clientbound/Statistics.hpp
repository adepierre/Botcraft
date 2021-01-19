#pragma once

#include "protocolCraft/BaseMessage.hpp"

#include <map>

namespace ProtocolCraft
{
    class Statistics : public BaseMessage<Statistics>
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
#else
#error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Statistics";
        }

        void SetCount(const int count_)
        {
            count = count_;
        }

#if PROTOCOL_VERSION < 346
        void SetStatistic(const std::map<std::string, int>& statistic_)
        {
            statistic = statistic_;
        }
#else
        void SetStatistic(const std::map<std::pair<int, int>, int>& statistic_)
        {
            statistic = statistic_;
        }
#endif


        const int GetCount() const
        {
            return count;
        }

#if PROTOCOL_VERSION < 346
        const std::map<std::string, int>& GetStatistic() const
        {
            return statistic;
        }
#else
        const std::map<std::pair<int, int>, int>& GetStatistic() const
        {
            return statistic;
        }
#endif


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            count = ReadVarInt(iter, length);
            statistic.clear();
            for (int i = 0; i < count; ++i)
            {
#if PROTOCOL_VERSION < 346
                std::string name = ReadString(iter, length);
                int value = ReadVarInt(iter, length);
                statistic[name] = value;
#else
                int category_id = ReadVarInt(iter, length);
                int statistic_id = ReadVarInt(iter, length);
                int value = ReadVarInt(iter, length);

                statistic[std::make_pair(category_id, statistic_id)] = value;
#endif
            }
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteVarInt(count, container);
            for (auto it = statistic.begin(); it != statistic.end(); ++it)
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

            object["count"] = picojson::value((double)count);
            object["statistic"] = picojson::value(picojson::array_type, false);
            picojson::array& array = object["statistic"].get<picojson::array>();
            for (auto it = statistic.begin(); it != statistic.end(); it++)
            {
                picojson::value value2(picojson::object_type, false);
                picojson::object& object2 = value2.get<picojson::object>();


#if PROTOCOL_VERSION < 346
                object2["name"] = picojson::value(it->first);
#else
                object2["category_id"] = picojson::value((double)it->first.first);
                object2["statistic_id"] = picojson::value((double)it->first.second);
#endif
                object2["value"] = picojson::value((double)it->second);
                array.push_back(value2);
            }

            return value;
        }

    private:
        int count;
#if PROTOCOL_VERSION < 346
        std::map<std::string, int> statistic;
#else
        std::map<std::pair<int, int>, int> statistic;
#endif

    };
} //ProtocolCraft