#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ServerboundPaddleBoatPacket : public BaseMessage<ServerboundPaddleBoatPacket>
    {
    public:
#if   PROTOCOL_VERSION == 340
        static constexpr int packet_id = 0x11;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 ||  \
      PROTOCOL_VERSION == 404
        static constexpr int packet_id = 0x14;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 ||  \
      PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 ||  \
      PROTOCOL_VERSION == 498 || PROTOCOL_VERSION == 573 ||  \
      PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578
        static constexpr int packet_id = 0x16;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736 ||  \
      PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 ||  \
      PROTOCOL_VERSION == 754
        static constexpr int packet_id = 0x17;
#elif PROTOCOL_VERSION == 755 || PROTOCOL_VERSION == 756 ||  \
      PROTOCOL_VERSION == 757 || PROTOCOL_VERSION == 758
        static constexpr int packet_id = 0x16;
#elif PROTOCOL_VERSION == 759
        static constexpr int packet_id = 0x18;
#elif PROTOCOL_VERSION == 760
        static constexpr int packet_id = 0x19;
#elif PROTOCOL_VERSION == 761
        static constexpr int packet_id = 0x18;
#elif PROTOCOL_VERSION == 762 || PROTOCOL_VERSION == 763
        static constexpr int packet_id = 0x19;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Paddle Boat";

        virtual ~ServerboundPaddleBoatPacket() override
        {

        }

        void SetLeft(const bool left_)
        {
            left = left_;
        }

        void SetRight(const bool right_)
        {
            right = right_;
        }


        bool GetLeft() const
        {
            return left;
        }

        bool GetRight() const
        {
            return right;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            left = ReadData<bool>(iter, length);
            right = ReadData<bool>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<bool>(left, container);
            WriteData<bool>(right, container);
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["left"] = left;
            output["right"] = right;

            return output;
        }

    private:
        bool left = false;
        bool right = false;

    };
} //ProtocolCraft
