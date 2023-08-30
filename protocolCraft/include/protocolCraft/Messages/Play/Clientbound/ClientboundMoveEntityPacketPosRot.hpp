#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundMoveEntityPacketPosRot : public BaseMessage<ClientboundMoveEntityPacketPosRot>
    {
    public:
#if   PROTOCOL_VERSION == 340
        static constexpr int packet_id = 0x27;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 ||  \
      PROTOCOL_VERSION == 404 || PROTOCOL_VERSION == 477 ||  \
      PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 ||  \
      PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498
        static constexpr int packet_id = 0x29;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 ||  \
      PROTOCOL_VERSION == 578
        static constexpr int packet_id = 0x2A;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736
        static constexpr int packet_id = 0x29;
#elif PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 ||  \
      PROTOCOL_VERSION == 754
        static constexpr int packet_id = 0x28;
#elif PROTOCOL_VERSION == 755 || PROTOCOL_VERSION == 756 ||  \
      PROTOCOL_VERSION == 757 || PROTOCOL_VERSION == 758
        static constexpr int packet_id = 0x2A;
#elif PROTOCOL_VERSION == 759
        static constexpr int packet_id = 0x27;
#elif PROTOCOL_VERSION == 760
        static constexpr int packet_id = 0x29;
#elif PROTOCOL_VERSION == 761
        static constexpr int packet_id = 0x28;
#elif PROTOCOL_VERSION == 762 || PROTOCOL_VERSION == 763
        static constexpr int packet_id = 0x2C;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Move Entity PosRot";

        virtual ~ClientboundMoveEntityPacketPosRot() override
        {

        }

        void SetEntityId(const int entity_id_)
        {
            entity_id = entity_id_;
        }

        void SetXA(const short x_a_)
        {
            x_a = x_a_;
        }

        void SetYA(const short y_a_)
        {
            y_a = y_a_;
        }

        void SetZA(const short z_a_)
        {
            z_a = z_a_;
        }

        void SetYRot(const unsigned char yRot_)
        {
            yRot = yRot_;
        }

        void SetXRot(const unsigned char xRot_)
        {
            xRot = xRot_;
        }

        void SetOnGround(const bool on_ground_)
        {
            on_ground = on_ground_;
        }

        int GetEntityId() const
        {
            return entity_id;
        }

        short GetXA() const
        {
            return x_a;
        }

        short GetYA() const
        {
            return y_a;
        }

        short GetZA() const
        {
            return z_a;
        }

        unsigned char GetYRot() const
        {
            return yRot;
        }

        unsigned char GetXRot() const
        {
            return xRot;
        }

        bool GetOnGround() const
        {
            return on_ground;
        }

    protected:
        virtual void ReadImpl(ReadIterator &iter, size_t &length) override
        {
            entity_id = ReadData<VarInt>(iter, length);
            x_a = ReadData<short>(iter, length);
            y_a = ReadData<short>(iter, length);
            z_a = ReadData<short>(iter, length);
            yRot = ReadData<unsigned char>(iter, length);
            xRot = ReadData<unsigned char>(iter, length);
            on_ground = ReadData<bool>(iter, length);
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
            WriteData<VarInt>(entity_id, container);
            WriteData<short>(x_a, container);
            WriteData<short>(y_a, container);
            WriteData<short>(z_a, container);
            WriteData<unsigned char>(yRot, container);
            WriteData<unsigned char>(xRot, container);
            WriteData<bool>(on_ground, container);
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["entity_id"] = entity_id;
            output["x_a"] = x_a;
            output["y_a"] = y_a;
            output["z_a"] = z_a;
            output["yRot"] = yRot;
            output["xRot"] = xRot;
            output["on_ground"] = on_ground;

            return output;
        }

    private:
        int entity_id = 0;
        short x_a = 0;
        short y_a = 0;
        short z_a = 0;
        unsigned char yRot = 0;
        unsigned char xRot = 0;
        bool on_ground = false;
    };
} //ProtocolCraft
