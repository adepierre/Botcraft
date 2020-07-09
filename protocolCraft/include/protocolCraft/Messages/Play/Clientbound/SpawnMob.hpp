#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class SpawnMob : public BaseMessage<SpawnMob>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 340 // 1.12.2
            return 0x03;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
            return 0x03;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
            return 0x03;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
            return 0x03;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16.X
            return 0x02;
#else
#error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Spawn Mob";
        }

        void SetEntityId(const int entity_id_)
        {
            entity_id = entity_id_;
        }

        void SetEntityUuid(const UUID& entity_uuid_)
        {
            entity_uuid = entity_uuid_;
        }

        void SetType(const int type_)
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

        void SetYaw(const Angle yaw_)
        {
            yaw = yaw_;
        }

        void SetPitch(const Angle pitch_)
        {
            pitch = pitch_;
        }

        void SetHeadPitch(const Angle head_pitch_)
        {
            head_pitch = head_pitch_;
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

#if PROTOCOL_VERSION < 550
        void SetRawEntityMetadata(const std::vector<unsigned char>& raw_entity_metadata_)
        {
            raw_entity_metadata = raw_entity_metadata_;
        }
#endif


        const int GetEntityId() const
        {
            return entity_id;
        }

        const UUID& GetEntityUuid() const
        {
            return entity_uuid;
        }

        const int GetType() const
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

        const Angle GetYaw() const
        {
            return yaw;
        }

        const Angle GetPitch() const
        {
            return pitch;
        }

        const Angle GetHeadPitch() const
        {
            return head_pitch;
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

#if PROTOCOL_VERSION < 550
        const std::vector<unsigned char>& GetRawEntityMetadata() const
        {
            return raw_entity_metadata;
        }
#endif


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            entity_id = ReadVarInt(iter, length);
            entity_uuid = ReadUUID(iter, length);
            type = ReadVarInt(iter, length);
            x = ReadData<double>(iter, length);
            y = ReadData<double>(iter, length);
            z = ReadData<double>(iter, length);
            yaw = ReadData<Angle>(iter, length);
            pitch = ReadData<Angle>(iter, length);
            head_pitch = ReadData<Angle>(iter, length);
            velocity_x = ReadData<short>(iter, length);
            velocity_y = ReadData<short>(iter, length);
            velocity_z = ReadData<short>(iter, length);
#if PROTOCOL_VERSION < 550
                raw_entity_metadata = ReadByteArray(iter, length, length);
#endif
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteVarInt(entity_id, container);
            WriteUUID(entity_uuid, container);
            WriteVarInt(type, container);
            WriteData<double>(x, container);
            WriteData<double>(y, container);
            WriteData<double>(z, container);
            WriteData<Angle>(yaw, container);
            WriteData<Angle>(pitch, container);
            WriteData<Angle>(head_pitch, container);
            WriteData<short>(velocity_x, container);
            WriteData<short>(velocity_y, container);
            WriteData<short>(velocity_z, container);
#if PROTOCOL_VERSION < 550
            WriteByteArray(raw_entity_metadata, container);
#endif
        }

        virtual const picojson::value SerializeImpl() const override
        {
            picojson::value value(picojson::object_type, false);
            picojson::object& object = value.get<picojson::object>();

            object["entity_id"] = picojson::value((double)entity_id);
            object["entity_uuid"] = picojson::value(entity_uuid);
            object["type"] = picojson::value((double)type);
            object["x"] = picojson::value(x);
            object["y"] = picojson::value(y);
            object["z"] = picojson::value(z);
            object["yaw"] = picojson::value((double)yaw);
            object["pitch"] = picojson::value((double)pitch);
            object["head_pitch"] = picojson::value((double)head_pitch);
            object["velocity_x"] = picojson::value((double)velocity_x);
            object["velocity_y"] = picojson::value((double)velocity_y);
            object["velocity_z"] = picojson::value((double)velocity_z);
#if PROTOCOL_VERSION < 550
            object["raw_entity_metadata"] = picojson::value("Vector of " + std::to_string(raw_entity_metadata.size()) + " unsigned char");
#endif

            return value;
        }

    private:
        int entity_id;
        UUID entity_uuid;
        int type;
        double x;
        double y;
        double z;
        Angle yaw;
        Angle pitch;
        Angle head_pitch;
        short velocity_x;
        short velocity_y;
        short velocity_z;
#if PROTOCOL_VERSION < 550
        std::vector<unsigned char> raw_entity_metadata;
#endif

    };
} //ProtocolCraft