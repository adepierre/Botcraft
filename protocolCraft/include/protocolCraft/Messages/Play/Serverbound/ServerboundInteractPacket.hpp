#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ServerboundInteractPacket : public BaseMessage<ServerboundInteractPacket>
    {
    public:
#if   PROTOCOL_VERSION == 340 /* 1.12.2 */
        static constexpr int packet_id = 0x0A;
#elif PROTOCOL_VERSION == 393 /* 1.13 */ || PROTOCOL_VERSION == 401 /* 1.13.1 */ ||  \
      PROTOCOL_VERSION == 404 /* 1.13.2 */
        static constexpr int packet_id = 0x0D;
#elif PROTOCOL_VERSION == 477 /* 1.14 */ || PROTOCOL_VERSION == 480 /* 1.14.1 */ ||  \
      PROTOCOL_VERSION == 485 /* 1.14.2 */ || PROTOCOL_VERSION == 490 /* 1.14.3 */ ||  \
      PROTOCOL_VERSION == 498 /* 1.14.4 */ || PROTOCOL_VERSION == 573 /* 1.15 */ ||  \
      PROTOCOL_VERSION == 575 /* 1.15.1 */ || PROTOCOL_VERSION == 578 /* 1.15.2 */ ||  \
      PROTOCOL_VERSION == 735 /* 1.16 */ || PROTOCOL_VERSION == 736 /* 1.16.1 */ ||  \
      PROTOCOL_VERSION == 751 /* 1.16.2 */ || PROTOCOL_VERSION == 753 /* 1.16.3 */ ||  \
      PROTOCOL_VERSION == 754 /* 1.16.4/5 */
        static constexpr int packet_id = 0x0E;
#elif PROTOCOL_VERSION == 755 /* 1.17 */ || PROTOCOL_VERSION == 756 /* 1.17.1 */ ||  \
      PROTOCOL_VERSION == 757 /* 1.18/.1 */ || PROTOCOL_VERSION == 758 /* 1.18.2 */
        static constexpr int packet_id = 0x0D;
#elif PROTOCOL_VERSION == 759 /* 1.19 */
        static constexpr int packet_id = 0x0F;
#elif PROTOCOL_VERSION == 760 /* 1.19.1/2 */
        static constexpr int packet_id = 0x10;
#elif PROTOCOL_VERSION == 761 /* 1.19.3 */
        static constexpr int packet_id = 0x0F;
#elif PROTOCOL_VERSION == 762 /* 1.19.4 */ || PROTOCOL_VERSION == 763 /* 1.20/.1 */
        static constexpr int packet_id = 0x10;
#elif PROTOCOL_VERSION == 764 /* 1.20.2 */
        static constexpr int packet_id = 0x12;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Interact";

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

#if PROTOCOL_VERSION > 722 /* > 1.15.2 */
        void SetUsingSecondaryAction(const bool using_secondary_action_)
        {
            using_secondary_action = using_secondary_action_;
        }
#endif


        int GetEntityId() const
        {
            return entity_id;
        }

        int GetAction() const
        {
            return action;
        }

        float GetLocationX() const
        {
            return location_x;
        }

        float GetLocationY() const
        {
            return location_y;
        }

        float GetLocationZ() const
        {
            return location_z;
        }

        int GetHand() const
        {
            return hand;
        }

#if PROTOCOL_VERSION > 722 /* > 1.15.2 */
        bool GetUsingSecondaryAction() const
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
#if PROTOCOL_VERSION > 722 /* > 1.15.2 */
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
#if PROTOCOL_VERSION > 722 /* > 1.15.2 */
            WriteData<bool>(using_secondary_action, container);
#endif
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

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
#if PROTOCOL_VERSION > 722 /* > 1.15.2 */
            output["using_secondary_action"] = using_secondary_action;
#endif

            return output;
        }

    private:
        int entity_id = 0;
        int action = 0;
        float location_x = 0.0f;
        float location_y = 0.0f;
        float location_z = 0.0f;
        int hand = 0;
#if PROTOCOL_VERSION > 722 /* > 1.15.2 */
        bool using_secondary_action = false;
#endif

    };
} //ProtocolCraft
