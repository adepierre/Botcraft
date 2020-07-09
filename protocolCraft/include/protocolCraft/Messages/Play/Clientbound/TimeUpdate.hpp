#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class TimeUpdate : public BaseMessage<TimeUpdate>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 340 // 1.12.2
            return 0x47;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
            return 0x4A;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
            return 0x4E;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
			return 0x4F;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16.X
            return 0x4E;
#else
            #error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Time Update";
        }

        void SetWorldAge(const long long int world_age_)
        {
            world_age = world_age_;
        }

        void SetTimeOfDay(const long long int time_of_day_)
        {
            time_of_day = time_of_day_;
        }

        const long long int GetWorldAge() const
        {
            return world_age;
        }

        const long long int GetTimeOfDay() const
        {
            return time_of_day;
        }

    protected:
        virtual void ReadImpl(ReadIterator &iter, size_t &length) override
        {
            world_age = ReadData<long long int>(iter, length);
            time_of_day = ReadData<long long int>(iter, length);
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
            WriteData<long long int>(world_age, container);
            WriteData<long long int>(time_of_day, container);
        }

        virtual const picojson::value SerializeImpl() const override
        {
            picojson::value value(picojson::object_type, false);
            picojson::object& object = value.get<picojson::object>();

            object["world_age"] = picojson::value((double)world_age);
            object["time_of_day"] = picojson::value((double)time_of_day);

            return value;
        }

    private:
        long long int world_age;
        long long int time_of_day;
    };
} //ProtocolCraft