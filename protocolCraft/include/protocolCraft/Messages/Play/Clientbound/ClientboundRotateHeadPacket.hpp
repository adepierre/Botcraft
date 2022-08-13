#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundRotateHeadPacket : public BaseMessage<ClientboundRotateHeadPacket>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 340 // 1.12.2
            return 0x36;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
            return 0x39;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
            return 0x3B;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
            return 0x3C;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16 or 1.16.1
            return 0x3B;
#elif PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 || PROTOCOL_VERSION == 754 // 1.16.2, 1.16.3, 1.16.4, 1.16.5
            return 0x3A;
#elif PROTOCOL_VERSION == 755 || PROTOCOL_VERSION == 756 // 1.17.X
            return 0x3E;
#elif PROTOCOL_VERSION == 757 || PROTOCOL_VERSION == 758 // 1.18, 1.18.1 or 1.18.2
            return 0x3E;
#elif PROTOCOL_VERSION == 759 // 1.19
            return 0x3C;
#elif PROTOCOL_VERSION == 760 // 1.19.1 or 1.19.2
            return 0x3F;
#else
#error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Rotate Head";
        }

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


        const int GetEntityId() const
        {
            return entity_id;
        }

        const Angle GetYHeadRot() const
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

        virtual const nlohmann::json SerializeImpl() const override
        {
            nlohmann::json output;

            output["entity_id"] = entity_id;
            output["y_head_rot"] = y_head_rot;

            return output;
        }

    private:
        int entity_id;
        Angle y_head_rot;

    };
} //ProtocolCraft