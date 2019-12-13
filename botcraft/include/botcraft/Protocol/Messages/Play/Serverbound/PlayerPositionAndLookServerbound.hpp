#pragma once

#include <iostream>

#include "botcraft/Protocol/BaseMessage.hpp"

#include "botcraft/Version.hpp"

namespace Botcraft
{
    class PlayerPositionAndLookServerbound : public BaseMessage<PlayerPositionAndLookServerbound>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 340 // 1.12.2
            return 0x0E;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
            return 0x11;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
            return 0x12;
#elif PROTOCOL_VERSION == 573
			return 0x12;
#else
            #error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Player Position And Look (serverbound)";
        }

        void SetX(const double d)
        {
            x = d;
        }

        void SetFeetY(const double d)
        {
            feet_y = d;
        }

        void SetZ(const double d)
        {
            z = d;
        }

        void SetYaw(const float f)
        {
            yaw = f;
        }

        void SetPitch(const float f)
        {
            pitch = f;
        }

        void SetOnGround(const bool b)
        {
            on_ground = b;
        }

    protected:
        virtual void ReadImpl(ReadIterator &iter, size_t &length) override
        {
            std::cerr << "Severbound message" << std::endl;
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
            WriteData<double>(x, container);
            WriteData<double>(feet_y, container);
            WriteData<double>(z, container);
            WriteData<float>(yaw, container);
            WriteData<float>(pitch, container);
            WriteData<bool>(on_ground, container);
        }

    private:
        double x;
        double feet_y;
        double z;

        float yaw;
        float pitch;
        bool on_ground;
    };
} //Botcraft