#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class EntityLook : public BaseMessage<EntityLook>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 340 // 1.12.2
            return 0x28;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
            return 0x2A;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
            return 0x2A;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
			return 0x2B;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16.0 or 1.16.1
            return 0x2A;
#elif PROTOCOL_VERSION == 751 // 1.16.2
            return 0x29;
#else
            #error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Entity Look";
        }

        void SetEntityId(const int entity_id_)
        {
            entity_id = entity_id_;
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
            yaw = ReadData<unsigned char>(iter, length);
            pitch = ReadData<unsigned char>(iter, length);
            on_ground = ReadData<bool>(iter, length);
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
            WriteVarInt(entity_id, container);
            WriteData<unsigned char>(yaw, container);
            WriteData<unsigned char>(pitch, container);
            WriteData<bool>(on_ground, container);
        }

        virtual const picojson::value SerializeImpl() const override
        {
            picojson::value value(picojson::object_type, false);
            picojson::object& object = value.get<picojson::object>();

            object["entity_id"] = picojson::value((double)entity_id);
            object["yaw"] = picojson::value((double)yaw);
            object["pitch"] = picojson::value((double)pitch);
            object["on_ground"] = picojson::value(on_ground);

            return value;
        }

    private:
        int entity_id;
        unsigned char yaw;
        unsigned char pitch;
        bool on_ground;
    };
} //ProtocolCraft