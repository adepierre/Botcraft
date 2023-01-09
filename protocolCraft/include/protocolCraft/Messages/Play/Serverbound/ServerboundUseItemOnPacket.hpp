#pragma once

#include "protocolCraft/BaseMessage.hpp"
#include "protocolCraft/Types/NetworkPosition.hpp"

namespace ProtocolCraft
{
    class ServerboundUseItemOnPacket : public BaseMessage<ServerboundUseItemOnPacket>
    {
    public:
#if PROTOCOL_VERSION == 340 // 1.12.2
        static constexpr int packet_id = 0x1F;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
        static constexpr int packet_id = 0x29;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
        static constexpr int packet_id = 0x2C;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
        static constexpr int packet_id = 0x2C;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16 or 1.16.1
        static constexpr int packet_id = 0x2D;
#elif PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 || PROTOCOL_VERSION == 754 // 1.16.2, 1.16.3, 1.16.4, 1.16.5
        static constexpr int packet_id = 0x2E;
#elif PROTOCOL_VERSION == 755 || PROTOCOL_VERSION == 756 // 1.17.X
        static constexpr int packet_id = 0x2E;
#elif PROTOCOL_VERSION == 757 || PROTOCOL_VERSION == 758 // 1.18, 1.18.1 or 1.18.2
        static constexpr int packet_id = 0x2E;
#elif PROTOCOL_VERSION == 759 // 1.19
        static constexpr int packet_id = 0x30;
#elif PROTOCOL_VERSION == 760 // 1.19.1 or 1.19.2
        static constexpr int packet_id = 0x31;
#elif PROTOCOL_VERSION == 761 // 1.19.3
        static constexpr int packet_id = 0x31;
#else
#error "Protocol version not implemented"
#endif
        static constexpr std::string_view packet_name = "Use Item On";

        virtual ~ServerboundUseItemOnPacket() override
        {

        }

        void SetHand(const int hand_)
        {
            hand = hand_;
        }

        void SetLocation(const NetworkPosition& location_)
        {
            location = location_;
        }

        void SetDirection(const int direction_)
        {
            direction = direction_;
        }

        void SetCursorPositionX(const float cursor_position_x_)
        {
            cursor_position_x = cursor_position_x_;
        }

        void SetCursorPositionY(const float cursor_position_y_)
        {
            cursor_position_y = cursor_position_y_;
        }

        void SetCursorPositionZ(const float cursor_position_z_)
        {
            cursor_position_z = cursor_position_z_;
        }

#if PROTOCOL_VERSION > 452
        void SetInside(const bool inside_)
        {
            inside = inside_;
        }
#endif

#if PROTOCOL_VERSION > 758
        void SetSequence(const int sequence_)
        {
            sequence = sequence_;
        }
#endif


        int GetHand() const
        {
            return hand;
        }

        const NetworkPosition& GetLocation() const
        {
            return location;
        }

        int GetDirection() const
        {
            return direction;
        }

        float GetCursorPositionX() const
        {
            return cursor_position_x;
        }

        float GetCursorPositionY() const
        {
            return cursor_position_y;
        }

        float GetCursorPositionZ() const
        {
            return cursor_position_z;
        }

#if PROTOCOL_VERSION > 452
        bool GetInside() const
        {
            return inside;
        }
#endif

#if PROTOCOL_VERSION > 758
        int GetSequence() const
        {
            return sequence;
        }
#endif


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
#if PROTOCOL_VERSION > 452
            hand = ReadData<VarInt>(iter, length);
#endif
            location = ReadData<NetworkPosition>(iter, length);
            direction = ReadData<VarInt>(iter, length);
#if PROTOCOL_VERSION < 453
            hand = ReadData<VarInt>(iter, length);
#endif
            cursor_position_x = ReadData<float>(iter, length);
            cursor_position_y = ReadData<float>(iter, length);
            cursor_position_z = ReadData<float>(iter, length);
#if PROTOCOL_VERSION > 452
            inside = ReadData<bool>(iter, length);
#endif
#if PROTOCOL_VERSION > 758
            sequence = ReadData<VarInt>(iter, length);
#endif
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
#if PROTOCOL_VERSION > 452
            WriteData<VarInt>(hand, container);
#endif
            WriteData<NetworkPosition>(location, container);
            WriteData<VarInt>(direction, container);
#if PROTOCOL_VERSION < 453
            WriteData<VarInt>(hand, container);
#endif
            WriteData<float>(cursor_position_x, container);
            WriteData<float>(cursor_position_y, container);
            WriteData<float>(cursor_position_z, container);
#if PROTOCOL_VERSION > 452
            WriteData<bool>(inside, container);
#endif
#if PROTOCOL_VERSION > 758
            WriteData<VarInt>(sequence, container);
#endif
        }

        virtual const nlohmann::json SerializeImpl() const override
        {
            nlohmann::json output;

            output["location"] = location.Serialize();
            output["direction"] = direction;
            output["cursor_position_x"] = cursor_position_x;
            output["cursor_position_y"] = cursor_position_y;
            output["cursor_position_z"] = cursor_position_z;
#if PROTOCOL_VERSION > 452
            output["inside"] = inside;
#endif
            output["hand"] = hand;
#if PROTOCOL_VERSION > 758
            output["sequence"] = sequence;
#endif


            return output;
        }

    private:
        NetworkPosition location;
        int direction;
        float cursor_position_x;
        float cursor_position_y;
        float cursor_position_z;
#if PROTOCOL_VERSION > 452
        bool inside;
#endif
        int hand;
#if PROTOCOL_VERSION > 758
        int sequence;
#endif

    };
} //ProtocolCraft
