#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class PlayerAbilitiesClientbound : public BaseMessage<PlayerAbilitiesClientbound>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 340 // 1.12.2
            return 0x2C;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
            return 0x2E;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
            return 0x31;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
			return 0x32;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16.0 or 1.16.1
            return 0x31;
#elif PROTOCOL_VERSION == 751 // 1.16.2
            return 0x30;
#else
            #error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Player Abilities (clientbound)";
        }

        void SetFlags(const char flags_)
        {
            flags = flags_;
        }

        void SetFlyingSpeed(const float flying_speed_)
        {
            flying_speed = flying_speed_;
        }

        void SetFieldOfViewModifier(const float field_of_view_modifier_)
        {
            field_of_view_modifier = field_of_view_modifier_;
        }

        const char GetFlags() const
        {
            return flags;
        }

        const float GetFlyingSpeed() const
        {
            return flying_speed;
        }

        const float GetFieldOfViewModifier() const
        {
            return field_of_view_modifier;
        }

    protected:
        virtual void ReadImpl(ReadIterator &iter, size_t &length) override
        {
            flags = ReadData<char>(iter, length);
            flying_speed = ReadData<float>(iter, length);
            field_of_view_modifier = ReadData<float>(iter, length);
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
            WriteData<char>(flags, container);
            WriteData<float>(flying_speed, container);
            WriteData<float>(field_of_view_modifier, container);
        }

        virtual const picojson::value SerializeImpl() const override
        {
            picojson::value value(picojson::object_type, false);
            picojson::object& object = value.get<picojson::object>();

            object["flags"] = picojson::value((double)flags);
            object["flying_speed"] = picojson::value((double)flying_speed);
            object["field_of_view_modifier"] = picojson::value((double)field_of_view_modifier);

            return value;
        }

    private:
        char flags;
        float flying_speed;
        float field_of_view_modifier;
    };
}