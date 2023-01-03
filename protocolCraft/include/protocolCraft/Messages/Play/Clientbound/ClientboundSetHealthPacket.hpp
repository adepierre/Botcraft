#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundSetHealthPacket : public BaseMessage<ClientboundSetHealthPacket>
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
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16 or 1.16.1
            return 0x49;
#elif PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 || PROTOCOL_VERSION == 754 // 1.16.2, 1.16.3, 1.16.4, 1.16.5
            return 0x49;
#elif PROTOCOL_VERSION == 755 || PROTOCOL_VERSION == 756 // 1.17.X
            return 0x52;
#elif PROTOCOL_VERSION == 757 || PROTOCOL_VERSION == 758 // 1.18, 1.18.1 or 1.18.2
            return 0x52;
#elif PROTOCOL_VERSION == 759 // 1.19
            return 0x52;
#elif PROTOCOL_VERSION == 760 // 1.19.1 or 1.19.2
            return 0x55;
#elif PROTOCOL_VERSION == 761 // 1.19.3
            return 0x53;
#else
#error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Set Health";
        }

        virtual ~ClientboundSetHealthPacket() override
        {

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
            food = ReadData<VarInt>(iter, length);
            food_saturation = ReadData<float>(iter, length);
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
            WriteData<float>(health, container);
            WriteData<VarInt>(food, container);
            WriteData<float>(food_saturation, container);
        }

        virtual const nlohmann::json SerializeImpl() const override
        {
            nlohmann::json output;

            output["health"] = health;
            output["food"] = food;
            output["food_saturation"] = food_saturation;

            return output;
        }

    private:
        float health;
        int food;
        float food_saturation;
    };
} //ProtocolCraft
