#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ServerboundSwingPacket : public BaseMessage<ServerboundSwingPacket>
    {
    public:
#if   PROTOCOL_VERSION == 340
        static constexpr int packet_id = 0x1D;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 ||  \
      PROTOCOL_VERSION == 404
        static constexpr int packet_id = 0x27;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 ||  \
      PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 ||  \
      PROTOCOL_VERSION == 498 || PROTOCOL_VERSION == 573 ||  \
      PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578
        static constexpr int packet_id = 0x2A;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736
        static constexpr int packet_id = 0x2B;
#elif PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 ||  \
      PROTOCOL_VERSION == 754 || PROTOCOL_VERSION == 755 ||  \
      PROTOCOL_VERSION == 756 || PROTOCOL_VERSION == 757 ||  \
      PROTOCOL_VERSION == 758
        static constexpr int packet_id = 0x2C;
#elif PROTOCOL_VERSION == 759
        static constexpr int packet_id = 0x2E;
#elif PROTOCOL_VERSION == 760 || PROTOCOL_VERSION == 761 ||  \
      PROTOCOL_VERSION == 762 || PROTOCOL_VERSION == 763
        static constexpr int packet_id = 0x2F;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Swing";

        virtual ~ServerboundSwingPacket() override
        {

        }

        void SetHand(const int hand_)
        {
            hand = hand_;
        }


        int GetHand() const
        {
            return hand;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            hand = ReadData<VarInt>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<VarInt>(hand, container);
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["hand"] = hand;

            return output;
        }

    private:
        int hand = 0;

    };
} //ProtocolCraft
