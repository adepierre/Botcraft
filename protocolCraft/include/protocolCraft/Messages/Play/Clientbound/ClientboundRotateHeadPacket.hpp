#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundRotateHeadPacket : public BaseMessage<ClientboundRotateHeadPacket>
    {
    public:
#if   PROTOCOL_VERSION == 340
        static constexpr int packet_id = 0x36;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 ||  \
      PROTOCOL_VERSION == 404
        static constexpr int packet_id = 0x39;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 ||  \
      PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 ||  \
      PROTOCOL_VERSION == 498
        static constexpr int packet_id = 0x3B;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 ||  \
      PROTOCOL_VERSION == 578
        static constexpr int packet_id = 0x3C;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736
        static constexpr int packet_id = 0x3B;
#elif PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 ||  \
      PROTOCOL_VERSION == 754
        static constexpr int packet_id = 0x3A;
#elif PROTOCOL_VERSION == 755 || PROTOCOL_VERSION == 756 ||  \
      PROTOCOL_VERSION == 757 || PROTOCOL_VERSION == 758
        static constexpr int packet_id = 0x3E;
#elif PROTOCOL_VERSION == 759
        static constexpr int packet_id = 0x3C;
#elif PROTOCOL_VERSION == 760
        static constexpr int packet_id = 0x3F;
#elif PROTOCOL_VERSION == 761
        static constexpr int packet_id = 0x3E;
#elif PROTOCOL_VERSION == 762 || PROTOCOL_VERSION == 763
        static constexpr int packet_id = 0x42;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Rotate Head";

        virtual ~ClientboundRotateHeadPacket() override
        {

        }

        void SetEntityId(const int entity_id_)
        {
            entity_id = entity_id_;
        }

        void SetYHeadRot(const Angle y_head_rot_)
        {
            y_head_rot = y_head_rot_;
        }


        int GetEntityId() const
        {
            return entity_id;
        }

        Angle GetYHeadRot() const
        {
            return y_head_rot;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            entity_id = ReadData<VarInt>(iter, length);
            y_head_rot = ReadData<Angle>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<VarInt>(entity_id, container);
            WriteData<Angle>(y_head_rot, container);
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["entity_id"] = entity_id;
            output["y_head_rot"] = y_head_rot;

            return output;
        }

    private:
        int entity_id = 0;
        Angle y_head_rot = 0;

    };
} //ProtocolCraft
