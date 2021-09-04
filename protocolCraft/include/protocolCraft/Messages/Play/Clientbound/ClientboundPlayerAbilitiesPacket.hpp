#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundPlayerAbilitiesPacket : public BaseMessage<ClientboundPlayerAbilitiesPacket>
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
#elif PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 || PROTOCOL_VERSION == 754 // 1.16.2, 1.16.3, 1.16.4, 1.16.5
            return 0x30;
#elif PROTOCOL_VERSION == 755 || PROTOCOL_VERSION == 756 // 1.17.X
            return 0x32;
#else
            #error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Player Abilities";
        }

        virtual ~ClientboundPlayerAbilitiesPacket() override
        {

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
        virtual void ReadImpl(ReadIterator &iter, size_t &length) override
        {
            flags = ReadData<char>(iter, length);
            flying_speed = ReadData<float>(iter, length);
            walking_speed = ReadData<float>(iter, length);
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
            WriteData<char>(flags, container);
            WriteData<float>(flying_speed, container);
            WriteData<float>(walking_speed, container);
        }

        virtual const nlohmann::json SerializeImpl() const override
        {
            nlohmann::json output;

            output["flags"] = flags;
            output["flying_speed"] = flying_speed;
            output["walking_speed"] = walking_speed;

            return output;
        }

    private:
        char flags;
        float flying_speed;
        float walking_speed;
    };
}