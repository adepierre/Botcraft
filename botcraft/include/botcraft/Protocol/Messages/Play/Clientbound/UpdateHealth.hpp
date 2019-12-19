#pragma once

#include <iostream>

#include "botcraft/Protocol/BaseMessage.hpp"

#include "botcraft/Version.hpp"

namespace Botcraft
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
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575
			return 0x49;
#else
            #error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Update Health";
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
            std::cerr << "Clientbound message" << std::endl;
        }

    private:
        float health;
        int food;
        float food_saturation;
    };
} //Botcraft