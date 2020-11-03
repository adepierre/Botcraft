#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class SpawnPlayer : public BaseMessage<SpawnPlayer>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 340 // 1.12.2
            return 0x05;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
            return 0x05;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
            return 0x05;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
            return 0x05;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16.0 or 1.16.1
            return 0x04;
#elif PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 || PROTOCOL_VERSION == 754 // 1.16.2, 1.16.3, 1.16.4
            return 0x04;
#else
#error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Spawn Player";
        }

        void SetEntityId(const int entity_id_)
        {
            entity_id = entity_id_;
        }

        void SetPlayerUuid(const UUID& player_uuid_)
        {
            player_uuid = player_uuid_;
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

#if PROTOCOL_VERSION < 550
        void SetRawMetadata(const std::vector<unsigned char> raw_metadata_)
        {
            raw_metadata = raw_metadata_;
        }
#endif


        const int GetEntityId() const
        {
            return entity_id;
        }

        const UUID& GetPlayerUuid() const
        {
            return player_uuid;
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

#if PROTOCOL_VERSION < 550
        const std::vector<unsigned char>& GetRawMetadata() const
        {
            return raw_metadata;
        }
#endif


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            entity_id = ReadVarInt(iter, length);
            player_uuid = ReadUUID(iter, length);
            x = ReadData<double>(iter, length);
            y = ReadData<double>(iter, length);
            z = ReadData<double>(iter, length);
            yaw = ReadData<Angle>(iter, length);
            pitch = ReadData<Angle>(iter, length);
#if PROTOCOL_VERSION < 550
            raw_metadata = ReadByteArray(iter, length, length);
#endif
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteVarInt(entity_id, container);
            WriteUUID(player_uuid, container);
            WriteData<double>(x, container);
            WriteData<double>(y, container);
            WriteData<double>(z, container);
            WriteData<Angle>(yaw, container);
            WriteData<Angle>(pitch, container); 
#if PROTOCOL_VERSION < 550
                WriteByteArray(raw_metadata, container);
#endif
        }

        virtual const picojson::value SerializeImpl() const override
        {
            picojson::value value(picojson::object_type, false);
            picojson::object& object = value.get<picojson::object>();

            object["entity_id"] = picojson::value((double)entity_id);
            object["player_uuid"] = picojson::value(player_uuid);
            object["x"] = picojson::value(x);
            object["y"] = picojson::value(y);
            object["z"] = picojson::value(z);
            object["yaw"] = picojson::value((double)yaw);
            object["pitch"] = picojson::value((double)pitch);
#if PROTOCOL_VERSION < 550
            object["raw_metadata"] = picojson::value("Vector of " + std::to_string(raw_metadata.size()) + " unsigned char");
#endif

            return value;
        }

    private:
        int entity_id;
        UUID player_uuid;
        double x;
        double y;
        double z;
        Angle yaw;
        Angle pitch;
#if PROTOCOL_VERSION < 550
        std::vector<unsigned char> raw_metadata;
#endif

    };
} //ProtocolCraft