#pragma once

#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundContainerClosePacket : public BaseMessage<ClientboundContainerClosePacket>
    {
    public:
#if   PROTOCOL_VERSION == 340
        static constexpr int packet_id = 0x12;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 ||  \
      PROTOCOL_VERSION == 404 || PROTOCOL_VERSION == 477 ||  \
      PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 ||  \
      PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498
        static constexpr int packet_id = 0x13;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 ||  \
      PROTOCOL_VERSION == 578
        static constexpr int packet_id = 0x14;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736
        static constexpr int packet_id = 0x13;
#elif PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 ||  \
      PROTOCOL_VERSION == 754
        static constexpr int packet_id = 0x12;
#elif PROTOCOL_VERSION == 755 || PROTOCOL_VERSION == 756 ||  \
      PROTOCOL_VERSION == 757 || PROTOCOL_VERSION == 758
        static constexpr int packet_id = 0x13;
#elif PROTOCOL_VERSION == 759 || PROTOCOL_VERSION == 760
        static constexpr int packet_id = 0x10;
#elif PROTOCOL_VERSION == 761
        static constexpr int packet_id = 0x0F;
#elif PROTOCOL_VERSION == 762 || PROTOCOL_VERSION == 763
        static constexpr int packet_id = 0x11;
#else
#error "Protocol version not implemented"
#endif

        static constexpr std::string_view packet_name = "Container Close";

        virtual ~ClientboundContainerClosePacket() override
        {

        }

        void SetContainerId(const unsigned char container_id_)
        {
            container_id = container_id_;
        }


        unsigned char GetContainerId() const
        {
            return container_id;
        }


    protected:
        virtual void ReadImpl(ReadIterator& iter, size_t& length) override
        {
            container_id = ReadData<unsigned char>(iter, length);
        }

        virtual void WriteImpl(WriteContainer& container) const override
        {
            WriteData<unsigned char>(container_id, container);
        }

        virtual Json::Value SerializeImpl() const override
        {
            Json::Value output;

            output["container_id"] = container_id;

            return output;
        }

    private:
        unsigned char container_id = 0;

    };
} //ProtocolCraft
