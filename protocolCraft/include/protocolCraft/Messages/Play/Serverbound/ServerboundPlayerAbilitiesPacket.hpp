#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ServerboundPlayerAbilitiesPacket : public BaseMessage<ServerboundPlayerAbilitiesPacket>
    {
    public:
#if PROTOCOL_VERSION == 340 // 1.12.2
        static constexpr int packet_id = 0x13;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
        static constexpr int packet_id = 0x17;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
        static constexpr int packet_id = 0x19;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
        static constexpr int packet_id = 0x19;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16 or 1.16.1
        static constexpr int packet_id = 0x1A;
#elif PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 || PROTOCOL_VERSION == 754 // 1.16.2, 1.16.3, 1.16.4, 1.16.5
        static constexpr int packet_id = 0x1A;
#elif PROTOCOL_VERSION == 755 || PROTOCOL_VERSION == 756 // 1.17.X
        static constexpr int packet_id = 0x19;
#elif PROTOCOL_VERSION == 757 || PROTOCOL_VERSION == 758 // 1.18, 1.18.1 or 1.18.2
        static constexpr int packet_id = 0x19;
#elif PROTOCOL_VERSION == 759 // 1.19
        static constexpr int packet_id = 0x1B;
#elif PROTOCOL_VERSION == 760 // 1.19.1 or 1.19.2
        static constexpr int packet_id = 0x1C;
#elif PROTOCOL_VERSION == 761 // 1.19.3
        static constexpr int packet_id = 0x1B;
#elif PROTOCOL_VERSION == 762 // 1.19.4
        static constexpr int packet_id = 0x1C;
#else
#error "Protocol version not implemented"
#endif
        static constexpr std::string_view packet_name = "Player Abilities";

        virtual ~ServerboundPlayerAbilitiesPacket() override
        {

        }

        void SetFlags(const char flags_)
        {
            flags = flags_;
        }

#if PROTOCOL_VERSION < 727
        void SetFlyingSpeed(const float flying_speed_)
        {
            flying_speed = flying_speed_;
        }

        void SetWalkingSpeed(const float walking_speed_)
        {
            walking_speed = walking_speed_;
        }
#endif


        char GetFlags() const
        {
            return flags;
        }

#if PROTOCOL_VERSION < 727
        float GetFlyingSpeed() const
        {
            return flying_speed;
        }

        float GetWalkingSpeed() const
        {
            return walking_speed;
        }
#endif


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            flags = ReadData<char>(iter, length);
#if PROTOCOL_VERSION < 727
            flying_speed = ReadData<float>(iter, length);
            walking_speed = ReadData<float>(iter, length);
#endif
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<char>(flags, container);
#if PROTOCOL_VERSION < 727
            WriteData<float>(flying_speed, container);
            WriteData<float>(walking_speed, container);
#endif
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["flags"] = flags;
#if PROTOCOL_VERSION < 727
            output["flying_speed"] = flying_speed;
            output["walking_speed"] = walking_speed;
#endif

            return output;
        }

    private:
        char flags;
#if PROTOCOL_VERSION < 727
        float flying_speed;
        float walking_speed;
#endif

    };
} //ProtocolCraft
