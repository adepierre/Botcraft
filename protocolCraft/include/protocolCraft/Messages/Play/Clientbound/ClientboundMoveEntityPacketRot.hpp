#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundMoveEntityPacketRot : public BaseMessage<ClientboundMoveEntityPacketRot>
    {
    public:
#if   PROTOCOL_VERSION == 340
        static constexpr int packet_id = 0x28;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 ||  \
      PROTOCOL_VERSION == 404 || PROTOCOL_VERSION == 477 ||  \
      PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 ||  \
      PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498
        static constexpr int packet_id = 0x2A;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 ||  \
      PROTOCOL_VERSION == 578
        static constexpr int packet_id = 0x2B;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736
        static constexpr int packet_id = 0x2A;
#elif PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 ||  \
      PROTOCOL_VERSION == 754
        static constexpr int packet_id = 0x29;
#elif PROTOCOL_VERSION == 755 || PROTOCOL_VERSION == 756 ||  \
      PROTOCOL_VERSION == 757 || PROTOCOL_VERSION == 758
        static constexpr int packet_id = 0x2B;
#elif PROTOCOL_VERSION == 759
        static constexpr int packet_id = 0x28;
#elif PROTOCOL_VERSION == 760
        static constexpr int packet_id = 0x2A;
#elif PROTOCOL_VERSION == 761
        static constexpr int packet_id = 0x29;
#elif PROTOCOL_VERSION == 762 || PROTOCOL_VERSION == 763
        static constexpr int packet_id = 0x2D;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Move Entity Rot";

        virtual ~ClientboundMoveEntityPacketRot() override
        {

        }

        void SetEntityId(const int entity_id_)
        {
            entity_id = entity_id_;
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
            yRot = ReadData<unsigned char>(iter, length);
            xRot = ReadData<unsigned char>(iter, length);
            on_ground = ReadData<bool>(iter, length);
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
            WriteData<VarInt>(entity_id, container);
            WriteData<unsigned char>(yRot, container);
            WriteData<unsigned char>(xRot, container);
            WriteData<bool>(on_ground, container);
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["entity_id"] = entity_id;
            output["yRot"] = yRot;
            output["xRot"] = xRot;
            output["on_ground"] = on_ground;

            return output;
        }

    private:
        int entity_id = 0;
        unsigned char yRot = 0;
        unsigned char xRot = 0;
        bool on_ground = false;
    };
} //ProtocolCraft
