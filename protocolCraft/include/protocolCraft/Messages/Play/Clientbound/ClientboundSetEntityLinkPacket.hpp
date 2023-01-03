#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundSetEntityLinkPacket : public BaseMessage<ClientboundSetEntityLinkPacket>
    {
    public:
        virtual const int GetId() const override
        {
#if PROTOCOL_VERSION == 340 // 1.12.2
            return 0x3D;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
            return 0x40;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
            return 0x44;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
            return 0x45;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16 or 1.16.1
            return 0x45;
#elif PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 || PROTOCOL_VERSION == 754 // 1.16.2, 1.16.3, 1.16.4, 1.16.5
            return 0x45;
#elif PROTOCOL_VERSION == 755 || PROTOCOL_VERSION == 756 // 1.17.X
            return 0x4E;
#elif PROTOCOL_VERSION == 757 || PROTOCOL_VERSION == 758 // 1.18, 1.18.1 or 1.18.2
            return 0x4E;
#elif PROTOCOL_VERSION == 759 // 1.19
            return 0x4E;
#elif PROTOCOL_VERSION == 760 // 1.19.1 or 1.19.2
            return 0x51;
#elif PROTOCOL_VERSION == 761 // 1.19.3
            return 0x4F;
#else
#error "Protocol version not implemented"
#endif
        }

        virtual const std::string GetName() const override
        {
            return "Set Entity Link";
        }

        virtual ~ClientboundSetEntityLinkPacket() override
        {

        }

        void SetSourceId(const int source_id_)
        {
            source_id = source_id_;
        }

        void SetDestId(const int dest_id_)
        {
            dest_id = dest_id_;
        }


        const int GetSourceId() const
        {
            return source_id;
        }

        const int GetDestId() const
        {
            return dest_id;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            source_id = ReadData<int>(iter, length);
            dest_id = ReadData<int>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<int>(source_id, container);
            WriteData<int>(dest_id, container);
        }

        virtual const nlohmann::json SerializeImpl() const override
        {
            nlohmann::json output;

            output["source_id"] = source_id;
            output["dest_id"] = dest_id;

            return output;
        }

    private:
        int source_id;
        int dest_id;

    };
} //ProtocolCraft
