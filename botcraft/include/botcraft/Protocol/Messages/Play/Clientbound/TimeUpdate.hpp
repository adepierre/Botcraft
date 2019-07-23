#pragma once

#include <iostream>

#include "botcraft/Protocol/BaseMessage.hpp"

#include "botcraft/Version.hpp"

namespace Botcraft
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
#else
            #error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Time Update";
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
            std::cerr << "Clientbound message" << std::endl;
        }

    private:
        long long int world_age;
        long long int time_of_day;
    };
} //Botcraft