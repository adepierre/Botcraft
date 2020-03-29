#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class PlayerAbilitiesServerbound : public BaseMessage<PlayerAbilitiesServerbound>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 340 // 1.12.2
            return 0x13;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
            return 0x17;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
            return 0x19;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
            return 0x19;
#else
#error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Player Abilities Serverbound";
        }

        void SetFlags(const char flags_)
        {
            flags = flags_;
        }

        void SetFlyingSpeed(const float flying_speed_)
        {
            flying_speed = flying_speed_;
        }

        void SetWalkingSpeed(const float walking_speed_)
        {
            walking_speed = walking_speed_;
        }


        const char GetFlags() const
        {
            return flags;
        }

        const float GetFlyingSpeed() const
        {
            return flying_speed;
        }

        const float GetWalkingSpeed() const
        {
            return walking_speed;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            flags = ReadData<char>(iter, length);
            flying_speed = ReadData<float>(iter, length);
            walking_speed = ReadData<float>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<char>(flags, container);
            WriteData<float>(flying_speed, container);
            WriteData<float>(walking_speed, container);
        }

        virtual const picojson::value SerializeImpl() const override
        {
            picojson::value value(picojson::object_type, false);
            picojson::object& object = value.get<picojson::object>();

            object["flags"] = picojson::value((double)flags);
            object["flying_speed"] = picojson::value((double)flying_speed);
            object["walking_speed"] = picojson::value((double)walking_speed);

            return value;
        }

    private:
        char flags;
        float flying_speed;
        float walking_speed;

    };
} //ProtocolCraft