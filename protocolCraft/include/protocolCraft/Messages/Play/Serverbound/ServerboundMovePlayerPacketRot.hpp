#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ServerboundMovePlayerPacketRot : public BaseMessage<ServerboundMovePlayerPacketRot>
    {
    public:
#if   PROTOCOL_VERSION == 340
        static constexpr int packet_id = 0x0F;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 ||  \
      PROTOCOL_VERSION == 404
        static constexpr int packet_id = 0x12;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 ||  \
      PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 ||  \
      PROTOCOL_VERSION == 498 || PROTOCOL_VERSION == 573 ||  \
      PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578
        static constexpr int packet_id = 0x13;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736 ||  \
      PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 ||  \
      PROTOCOL_VERSION == 754
        static constexpr int packet_id = 0x14;
#elif PROTOCOL_VERSION == 755 || PROTOCOL_VERSION == 756 ||  \
      PROTOCOL_VERSION == 757 || PROTOCOL_VERSION == 758
        static constexpr int packet_id = 0x13;
#elif PROTOCOL_VERSION == 759
        static constexpr int packet_id = 0x15;
#elif PROTOCOL_VERSION == 760
        static constexpr int packet_id = 0x16;
#elif PROTOCOL_VERSION == 761
        static constexpr int packet_id = 0x15;
#elif PROTOCOL_VERSION == 762 || PROTOCOL_VERSION == 763
        static constexpr int packet_id = 0x16;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Move Player Rot";

        virtual ~ServerboundMovePlayerPacketRot() override
        {

        }

        void SetYRot(const float yRot_)
        {
            yRot = yRot_;
        }

        void SetXRot(const float xRot_)
        {
            xRot = xRot_;
        }

        void SetOnGround(const bool on_ground_)
        {
            on_ground = on_ground_;
        }


        float GetYRot() const
        {
            return yRot;
        }

        float GetXRot() const
        {
            return xRot;
        }

        bool GetOnGround() const
        {
            return on_ground;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            yRot = ReadData<float>(iter, length);
            xRot = ReadData<float>(iter, length);
            on_ground = ReadData<bool>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<float>(yRot, container);
            WriteData<float>(xRot, container);
            WriteData<bool>(on_ground, container);
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["yRot"] = yRot;
            output["xRot"] = xRot;
            output["on_ground"] = on_ground;

            return output;
        }

    private:
        float yRot = 0.0f;
        float xRot = 0.0f;
        bool on_ground = false;

    };
} //ProtocolCraft
