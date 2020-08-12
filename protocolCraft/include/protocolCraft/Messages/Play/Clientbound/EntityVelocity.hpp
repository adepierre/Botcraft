#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class EntityVelocity : public BaseMessage<EntityVelocity>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 340 // 1.12.2
            return 0x3E;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
            return 0x41;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
            return 0x45;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
            return 0x46;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16.0 or 1.16.1
            return 0x46;
#elif PROTOCOL_VERSION == 751 // 1.16.2
            return 0x46;
#else
#error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Entity Velocity";
        }

        void SetEntityId(const int entity_id_)
        {
            entity_id = entity_id_;
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
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            entity_id = ReadVarInt(iter, length);
            velocity_x = ReadData<short>(iter, length);
            velocity_y = ReadData<short>(iter, length);
            velocity_z = ReadData<short>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteVarInt(entity_id, container);
            WriteData<short>(velocity_x, container);
            WriteData<short>(velocity_y, container);
            WriteData<short>(velocity_z, container);
        }

        virtual const picojson::value SerializeImpl() const override
        {
            picojson::value value(picojson::object_type, false);
            picojson::object& object = value.get<picojson::object>();

            object["entity_id"] = picojson::value((double)entity_id);
            object["velocity_x"] = picojson::value((double)velocity_x);
            object["velocity_y"] = picojson::value((double)velocity_y);
            object["velocity_z"] = picojson::value((double)velocity_z);

            return value;
        }

    private:
        int entity_id;
        short velocity_x;
        short velocity_y;
        short velocity_z;

    };
} //ProtocolCraft