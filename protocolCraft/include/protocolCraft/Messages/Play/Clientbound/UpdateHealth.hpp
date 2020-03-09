#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class UpdateHealth : public BaseMessage<UpdateHealth>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 340 // 1.12.2
            return 0x41;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
            return 0x44;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
            return 0x48;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
			return 0x49;
#else
            #error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Update Health";
        }

        void SetHealth(const float health_)
        {
            health = health_;
        }

        void SetFood(const int food_)
        {
            food = food_;
        }

        void SetFoodSaturation(const float food_saturation_)
        {
            food_saturation = food_saturation_;
        }

        const float GetHealth() const
        {
            return health;
        }

        const int GetFood() const
        {
            return food;
        }

        const float GetFoodSaturation() const
        {
            return food_saturation;
        }

    protected:
        virtual void ReadImpl(ReadIterator &iter, size_t &length) override
        {
            health = ReadData<float>(iter, length);
            food = ReadVarInt(iter, length);
            food_saturation = ReadData<float>(iter, length);
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
            WriteData<float>(health, container);
            WriteVarInt(food, container);
            WriteData<float>(food_saturation, container);
        }

        virtual const picojson::value SerializeImpl() const override
        {
            picojson::value value(picojson::object_type, false);
            picojson::object& object = value.get<picojson::object>();

            object["health"] = picojson::value((double)health);
            object["food"] = picojson::value((double)food);
            object["food_saturation"] = picojson::value((double)food_saturation);

            return value;
        }

    private:
        float health;
        int food;
        float food_saturation;
    };
} //ProtocolCraft