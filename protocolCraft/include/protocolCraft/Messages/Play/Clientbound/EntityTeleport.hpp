#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class EntityTeleport : public BaseMessage<EntityTeleport>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 340 // 1.12.2
            return 0x4C;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
            return 0x50;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
            return 0x56;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
			return 0x57;
#else
            #error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Entity Teleport";
        }

        void SetEntityId(const int entity_id_)
        {
            entity_id = entity_id_;
        }

        void SetX(const double x_)
        {
            x = x_;
        }

        void SetY(const double y_)
        {
            y = y_;
        }

        void SetZ(const double z_)
        {
            z = z_;
        }

        void SetYaw(const unsigned char yaw_)
        {
            yaw = yaw_;
        }

        void SetPitch(const unsigned char pitch_)
        {
            pitch = pitch_;
        }

        void SetOnGround(const bool on_ground_)
        {
            on_ground = on_ground_;
        }

        const int GetEntityId() const
        {
            return entity_id;
        }

        const double GetX() const
        {
            return x;
        }

        const double GetY() const
        {
            return y;
        }

        const double GetZ() const
        {
            return z;
        }

        const unsigned char GetYaw() const
        {
            return yaw;
        }

        const unsigned char GetPitch() const
        {
            return pitch;
        }

        const bool GetOnGround() const
        {
            return on_ground;
        }

    protected:
        virtual void ReadImpl(ReadIterator &iter, size_t &length) override
        {
            entity_id = ReadVarInt(iter, length);
            x = ReadData<double>(iter, length);
            y = ReadData<double>(iter, length);
            z = ReadData<double>(iter, length);
            yaw = ReadData<unsigned char>(iter, length);
            pitch = ReadData<unsigned char>(iter, length);
            on_ground = ReadData<bool>(iter, length);
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
            WriteVarInt(entity_id, container);
            WriteData<double>(x, container);
            WriteData<double>(y, container);
            WriteData<double>(z, container);
            WriteData<unsigned char>(yaw, container);
            WriteData<unsigned char>(pitch, container);
            WriteData<bool>(on_ground, container);
        }

        virtual const picojson::value SerializeImpl() const override
        {
            picojson::value value(picojson::object_type, false);
            picojson::object& object = value.get<picojson::object>();

            object["entity_id"] = picojson::value((double)entity_id);
            object["x"] = picojson::value(x);
            object["y"] = picojson::value(y);
            object["z"] = picojson::value(z);
            object["yaw"] = picojson::value((double)yaw);
            object["pitch"] = picojson::value((double)pitch);
            object["on_ground"] = picojson::value(on_ground);

            return value;
        }

    private:
        int entity_id;
        double x;
        double y;
        double z;
        unsigned char yaw;
        unsigned char pitch;
        bool on_ground;
    };
} //ProtocolCraft