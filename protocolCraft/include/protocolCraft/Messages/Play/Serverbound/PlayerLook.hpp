#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    // Player rotation on 1.14+
    class PlayerLook : public BaseMessage<PlayerLook>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 340 // 1.12.2
            return 0x0F;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
            return 0x12;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
            return 0x13;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
            return 0x13;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16.0 or 1.16.1
            return 0x14;
#elif PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 || PROTOCOL_VERSION == 754 // 1.16.2, 1.16.3, 1.16.4, 1.16.5
            return 0x14;
#else
            #error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Player Look";
        }

        void SetYaw(const float yaw_)
        {
            yaw = yaw_;
        }

        void SetPitch(const float pitch_)
        {
            pitch = pitch_;
        }

        void SetOnGround(const bool on_ground_)
        {
            on_ground = on_ground_;
        }


        const float GetYaw() const
        {
            return yaw;
        }

        const float GetPitch() const
        {
            return pitch;
        }

        const bool GetOnGround() const
        {
            return on_ground;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            yaw = ReadData<float>(iter, length);
            pitch = ReadData<float>(iter, length);
            on_ground = ReadData<bool>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<float>(yaw, container);
            WriteData<float>(pitch, container);
            WriteData<bool>(on_ground, container);
        }

        virtual const picojson::value SerializeImpl() const override
        {
            picojson::value value(picojson::object_type, false);
            picojson::object& object = value.get<picojson::object>();

            object["yaw"] = picojson::value((double)yaw);
            object["pitch"] = picojson::value((double)pitch);
            object["on_ground"] = picojson::value(on_ground);

            return value;
        }

    private:
        float yaw;
        float pitch;
        bool on_ground;

    };
} //ProtocolCraft