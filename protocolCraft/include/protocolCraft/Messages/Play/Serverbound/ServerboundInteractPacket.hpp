#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ServerboundInteractPacket : public BaseMessage<ServerboundInteractPacket>
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
#elif PROTOCOL_VERSION == 755 || PROTOCOL_VERSION == 756 // 1.17.X
            return 0x0D;
#else
            #error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Interact";
        }

        virtual ~ServerboundInteractPacket() override
        {

        }

        void SetEntityId(const int entity_id_)
        {
            entity_id = entity_id_;
        }

        void SetAction(const int action_)
        {
            action = action_;
        }

        void SetLocationX(const float location_x_)
        {
            location_x = location_x_;
        }

        void SetLocationY(const float location_y_)
        {
            location_y = location_y_;
        }

        void SetLocationZ(const float location_z_)
        {
            location_z = location_z_;
        }

        void SetHand(const int hand_)
        {
            hand = hand_;
        }

#if PROTOCOL_VERSION > 722
        void SetUsingSecondaryAction(const bool using_secondary_action_)
        {
            using_secondary_action = using_secondary_action_;
        }
#endif


        const int GetEntityId() const
        {
            return entity_id;
        }

        const int GetAction() const
        {
            return action;
        }

        const float GetLocationX() const
        {
            return location_x;
        }

        const float GetLocationY() const
        {
            return location_y;
        }

        const float GetLocationZ() const
        {
            return location_z;
        }

        const int GetHand() const
        {
            return hand;
        }

#if PROTOCOL_VERSION > 722
        const bool GetUsingSecondaryAction() const
        {
            return using_secondary_action;
        }
#endif

    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            entity_id = ReadData<VarInt>(iter, length);
            action = ReadData<VarInt>(iter, length);
            if (action == 2)
            {
                location_x = ReadData<float>(iter, length);
                location_y = ReadData<float>(iter, length);
                location_z = ReadData<float>(iter, length);
            }
            if (action == 0 || action == 2)
            {
                hand = ReadData<VarInt>(iter, length);
            }
#if PROTOCOL_VERSION > 722
            using_secondary_action = ReadData<bool>(iter, length);
#endif
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<VarInt>(entity_id, container);
            WriteData<VarInt>(action, container); 
            if (action == 2)
            {
                WriteData<float>(location_x, container);
                WriteData<float>(location_y, container);
                WriteData<float>(location_z, container);
            }
            if (action == 0 || action == 2)
            {
                WriteData<VarInt>(hand, container);
            }
#if PROTOCOL_VERSION > 722
            WriteData<bool>(using_secondary_action, container);
#endif
        }

        virtual const nlohmann::json SerializeImpl() const override
        {
            nlohmann::json output;

            output["entity_id"] = entity_id;
            output["action"] = action;
            if (action == 2)
            {
                output["location_x"] = location_x;
                output["location_y"] = location_y;
                output["location_z"] = location_z;
            }
            if (action == 0 || action == 2)
            {
                output["hand"] = hand;
            }
#if PROTOCOL_VERSION > 722
            output["using_secondary_action"] = using_secondary_action;
#endif

            return output;
        }

    private:
        int entity_id;
        int action;
        float location_x;
        float location_y;
        float location_z;
        int hand;
#if PROTOCOL_VERSION > 722
        bool using_secondary_action;
#endif

    };
} //ProtocolCraft