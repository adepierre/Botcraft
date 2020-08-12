#pragma once

#if PROTOCOL_VERSION > 351
#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class FacePlayer : public BaseMessage<FacePlayer>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
            return 0x31;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
            return 0x34;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
            return 0x35;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16.0 or 1.16.1
            return 0x34;
#elif PROTOCOL_VERSION == 751 // 1.16.2
            return 0x33;
#else
#error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Face Player";
        }

        void SetFeetEyes(const int feet_eyes_)
        {
            feet_eyes = feet_eyes_;
        }

        void SetTargetX(const double target_x_)
        {
            target_x = target_x_;
        }

        void SetTargetY(const double target_y_)
        {
            target_y = target_y_;
        }

        void SetTargetZ(const double target_z_)
        {
            target_z = target_z_;
        }

        void SetIsEntity(const bool is_entity_)
        {
            is_entity = is_entity_;
        }

        void SetEntityId(const int entity_id_)
        {
            entity_id = entity_id_;
        }

        void SetEntityFeetEyes(const int entity_feet_eyes_)
        {
            entity_feet_eyes = entity_feet_eyes_;
        }


        const int GetFeetEyes() const
        {
            return feet_eyes;
        }

        const double GetTargetX() const
        {
            return target_x;
        }

        const double GetTargetY() const
        {
            return target_y;
        }

        const double GetTargetZ() const
        {
            return target_z;
        }

        const bool GetIsEntity() const
        {
            return is_entity;
        }

        const int GetEntityId() const
        {
            return entity_id;
        }

        const int GetEntityFeetEyes() const
        {
            return entity_feet_eyes;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            feet_eyes = ReadVarInt(iter, length);
            target_x = ReadData<double>(iter, length);
            target_y = ReadData<double>(iter, length);
            target_z = ReadData<double>(iter, length);
            is_entity = ReadData<bool>(iter, length);
            if (is_entity)
            {
                entity_id = ReadVarInt(iter, length);
                entity_feet_eyes = ReadVarInt(iter, length);
            }
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteVarInt(feet_eyes, container);
            WriteData<double>(target_x, container);
            WriteData<double>(target_y, container);
            WriteData<double>(target_z, container);
            WriteData<bool>(is_entity, container);
            if (is_entity)
            {
                WriteVarInt(entity_id, container);
                WriteVarInt(entity_feet_eyes, container);
            }
        }

        virtual const picojson::value SerializeImpl() const override
        {
            picojson::value value(picojson::object_type, false);
            picojson::object& object = value.get<picojson::object>();

            object["feet_eyes"] = picojson::value((double)feet_eyes);
            object["target_x"] = picojson::value(target_x);
            object["target_y"] = picojson::value(target_y);
            object["target_z"] = picojson::value(target_z);
            object["is_entity"] = picojson::value(is_entity);
            if (is_entity)
            {
                object["entity_id"] = picojson::value((double)entity_id);
                object["entity_feet_eyes"] = picojson::value((double)entity_feet_eyes);
            }

            return value;
        }

    private:
        int feet_eyes;
        double target_x;
        double target_y;
        double target_z;
        bool is_entity;
        int entity_id;
        int entity_feet_eyes;

    };
} //ProtocolCraft
#endif
