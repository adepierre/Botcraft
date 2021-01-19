#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    // Was use entity in 1.12.2 and 1.13.x
    class InteractEntity : public BaseMessage<InteractEntity>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 340 // 1.12.2
            return 0x0A;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
            return 0x0D;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
            return 0x0E;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
            return 0x0E;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16.0 or 1.16.1
            return 0x0E;
#elif PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 || PROTOCOL_VERSION == 754 // 1.16.2, 1.16.3, 1.16.4, 1.16.5
            return 0x0E;
#else
            #error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Interact Entity";
        }

        void SetEntityId(const int entity_id_)
        {
            entity_id = entity_id_;
        }

        void SetType(const int type_)
        {
            type = type_;
        }

        void SetTargetX(const float target_x_)
        {
            target_x = target_x_;
        }

        void SetTargetY(const float target_y_)
        {
            target_y = target_y_;
        }

        void SetTargetZ(const float target_z_)
        {
            target_z = target_z_;
        }

        void SetHand(const int hand_)
        {
            hand = hand_;
        }

#if PROTOCOL_VERSION > 722
        void SetSneaking(const bool sneaking_)
        {
            sneaking = sneaking_;
        }
#endif


        const int GetEntityId() const
        {
            return entity_id;
        }

        const int GetType() const
        {
            return type;
        }

        const float GetTargetX() const
        {
            return target_x;
        }

        const float GetTargetY() const
        {
            return target_y;
        }

        const float GetTargetZ() const
        {
            return target_z;
        }

        const int GetHand() const
        {
            return hand;
        }

#if PROTOCOL_VERSION > 722
        const bool GetSneaking() const
        {
            return sneaking;
        }
#endif

    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            entity_id = ReadVarInt(iter, length);
            type = ReadVarInt(iter, length);
            if (type == 2)
            {
                target_x = ReadData<float>(iter, length);
                target_y = ReadData<float>(iter, length);
                target_z = ReadData<float>(iter, length);
            }
            if (type == 0 || type == 2)
            {
                hand = ReadVarInt(iter, length);
            }
#if PROTOCOL_VERSION > 722
            sneaking = ReadData<bool>(iter, length);
#endif
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteVarInt(entity_id, container);
            WriteVarInt(type, container); 
            if (type == 2)
            {
                WriteData<float>(target_x, container);
                WriteData<float>(target_y, container);
                WriteData<float>(target_z, container);
            }
            if (type == 0 || type == 2)
            {
                WriteVarInt(hand, container);
            }
#if PROTOCOL_VERSION > 722
            WriteData<bool>(sneaking, container);
#endif
        }

        virtual const picojson::value SerializeImpl() const override
        {
            picojson::value value(picojson::object_type, false);
            picojson::object& object = value.get<picojson::object>();

            object["entity_id"] = picojson::value((double)entity_id);
            object["type"] = picojson::value((double)type);
            if (type == 2)
            {
                object["target_x"] = picojson::value((double)target_x);
                object["target_y"] = picojson::value((double)target_y);
                object["target_z"] = picojson::value((double)target_z);
            }
            if (type == 0 || type == 2)
            {
                object["hand"] = picojson::value((double)hand);
            }
#if PROTOCOL_VERSION > 722
            object["sneaking"] = picojson::value(sneaking);
#endif

            return value;
        }

    private:
        int entity_id;
        int type;
        float target_x;
        float target_y;
        float target_z;
        int hand;
#if PROTOCOL_VERSION > 722
        bool sneaking;
#endif

    };
} //ProtocolCraft