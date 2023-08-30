#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundSetHealthPacket : public BaseMessage<ClientboundSetHealthPacket>
    {
    public:
#if   PROTOCOL_VERSION == 340
        static constexpr int packet_id = 0x41;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 ||  \
      PROTOCOL_VERSION == 404
        static constexpr int packet_id = 0x44;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 ||  \
      PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 ||  \
      PROTOCOL_VERSION == 498
        static constexpr int packet_id = 0x48;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 ||  \
      PROTOCOL_VERSION == 578 || PROTOCOL_VERSION == 735 ||  \
      PROTOCOL_VERSION == 736 || PROTOCOL_VERSION == 751 ||  \
      PROTOCOL_VERSION == 753 || PROTOCOL_VERSION == 754
        static constexpr int packet_id = 0x49;
#elif PROTOCOL_VERSION == 755 || PROTOCOL_VERSION == 756 ||  \
      PROTOCOL_VERSION == 757 || PROTOCOL_VERSION == 758 ||  \
      PROTOCOL_VERSION == 759
        static constexpr int packet_id = 0x52;
#elif PROTOCOL_VERSION == 760
        static constexpr int packet_id = 0x55;
#elif PROTOCOL_VERSION == 761
        static constexpr int packet_id = 0x53;
#elif PROTOCOL_VERSION == 762 || PROTOCOL_VERSION == 763
        static constexpr int packet_id = 0x57;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Set Health";

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

        float GetHealth() const
        {
            return health;
        }

        int GetFood() const
        {
            return food;
        }

        float GetFoodSaturation() const
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

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["health"] = health;
            output["food"] = food;
            output["food_saturation"] = food_saturation;

            return output;
        }

    private:
        float health = 0.0f;
        int food = 0;
        float food_saturation = 0.0f;
    };
} //ProtocolCraft
