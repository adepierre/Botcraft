#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class SpawnObject : public BaseMessage<SpawnObject>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 340 // 1.12.2
            return 0x00;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
            return 0x00;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
            return 0x00;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
			return 0x00;
#else
            #error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Spawn Object";
        }

        void SetEntityId(const int entity_id_)
        {
            entity_id = entity_id_;
        }

        void SetObjectUUID(const UUID& object_uuid_)
        {
            object_uuid = object_uuid_;
        }

        void SetType(const char type_)
        {
            type = type_;
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

        void SetPitch(const Angle pitch_)
        {
            pitch = pitch_;
        }

        void SetYaw(const Angle yaw_)
        {
            yaw = yaw_;
        }

        void SetData(const int data_)
        {
            data = data_;
        }

        void SetVelocityX(const short velocity_x_)
        {
            velocity_x = velocity_x_;
        }

        void SetVelocityY(const short velocity_y_)
        {
            velocity_y = velocity_y_;
        }

        void SetVelocityZ(const short velocity_z_)
        {
            velocity_z = velocity_z_;
        }

        const int GetEntityId() const
        {
            return entity_id;
        }

        const UUID& GetObjectUUID() const
        {
            return object_uuid;
        }

        const char GetType() const
        {
            return type;
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

        const Angle GetPitch() const
        {
            return pitch;
        }

        const Angle GetYaw() const
        {
            return yaw;
        }

        const int GetData() const
        {
            return data;
        }

        const short GetVelocityX() const
        {
            return velocity_x;
        }

        const short GetVelocityY() const
        {
            return velocity_y;
        }

        const short GetVelocityZ() const
        {
            return velocity_z;
        }

    protected:
        virtual void ReadImpl(ReadIterator &iter, size_t &length) override
        {
            entity_id = ReadVarInt(iter, length);
            object_uuid = ReadUUID(iter, length);
#if PROTOCOL_VERSION < 458
            type = ReadData<char>(iter, length);
#else
            type = ReadVarInt(iter, length);
#endif
            x = ReadData<double>(iter, length);
            y = ReadData<double>(iter, length);
            z = ReadData<double>(iter, length);
            pitch = ReadData<Angle>(iter, length);
            yaw = ReadData<Angle>(iter, length);
            data = ReadData<int>(iter, length);
            velocity_x = ReadData<short>(iter, length);
            velocity_y = ReadData<short>(iter, length);
            velocity_z = ReadData<short>(iter, length);
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
            WriteVarInt(entity_id, container);
            WriteUUID(object_uuid, container);
#if PROTOCOL_VERSION < 458
            WriteData<char>(type, container);
#else
            WriteVarInt(type, container);
#endif
            WriteData<double>(x, container);
            WriteData<double>(y, container);
            WriteData<double>(z, container);
            WriteData<Angle>(pitch, container);
            WriteData<Angle>(yaw, container);
            WriteData<int>(data, container);
            WriteData<short>(velocity_x, container);
            WriteData<short>(velocity_y, container);
            WriteData<short>(velocity_z, container);
        }

        virtual const picojson::value SerializeImpl() const override
        {
            picojson::value value(picojson::object_type, false);
            picojson::object& object = value.get<picojson::object>();

            object["entity_id"] = picojson::value((double)entity_id);
            object["object_uuid"] = picojson::value(object_uuid);
            object["type"] = picojson::value((double)type);
            object["x"] = picojson::value((double)x);
            object["y"] = picojson::value((double)y);
            object["z"] = picojson::value((double)z);
            object["pitch"] = picojson::value((double)pitch);
            object["yaw"] = picojson::value((double)yaw);
            object["data"] = picojson::value((double)data);
            object["velocity_x"] = picojson::value((double)velocity_x);
            object["velocity_y"] = picojson::value((double)velocity_y);
            object["velocity_z"] = picojson::value((double)velocity_z);

            return value;
    }

    private:
        int entity_id;
        UUID object_uuid;
#if PROTOCOL_VERSION < 458
        char type;
#else
        int type
#endif
        double x;
        double y;
        double z;
        Angle pitch;
        Angle yaw;
        int data;
        short velocity_x;
        short velocity_y;
        short velocity_z;

    };
} //ProtocolCraft