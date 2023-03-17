#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundSetEntityLinkPacket : public BaseMessage<ClientboundSetEntityLinkPacket>
    {
    public:
#if PROTOCOL_VERSION == 340 // 1.12.2
        static constexpr int packet_id = 0x3D;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
        static constexpr int packet_id = 0x40;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
        static constexpr int packet_id = 0x44;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
        static constexpr int packet_id = 0x45;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16 or 1.16.1
        static constexpr int packet_id = 0x45;
#elif PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 || PROTOCOL_VERSION == 754 // 1.16.2, 1.16.3, 1.16.4, 1.16.5
        static constexpr int packet_id = 0x45;
#elif PROTOCOL_VERSION == 755 || PROTOCOL_VERSION == 756 // 1.17.X
        static constexpr int packet_id = 0x4E;
#elif PROTOCOL_VERSION == 757 || PROTOCOL_VERSION == 758 // 1.18, 1.18.1 or 1.18.2
        static constexpr int packet_id = 0x4E;
#elif PROTOCOL_VERSION == 759 // 1.19
        static constexpr int packet_id = 0x4E;
#elif PROTOCOL_VERSION == 760 // 1.19.1 or 1.19.2
        static constexpr int packet_id = 0x51;
#elif PROTOCOL_VERSION == 761 // 1.19.3
        static constexpr int packet_id = 0x4F;
#elif PROTOCOL_VERSION == 762 // 1.19.4
static constexpr int packet_id = 0x53;
#else
#error "Protocol version not implemented"
#endif
        static constexpr std::string_view packet_name = "Set Entity Link";

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


        int GetSourceId() const
        {
            return source_id;
        }

        int GetDestId() const
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

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["source_id"] = source_id;
            output["dest_id"] = dest_id;

            return output;
        }

    private:
        int source_id;
        int dest_id;

    };
} //ProtocolCraft
