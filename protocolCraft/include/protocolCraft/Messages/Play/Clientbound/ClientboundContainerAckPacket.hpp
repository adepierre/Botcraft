#pragma once

#if PROTOCOL_VERSION < 755 //1.17
#include "protocolCraft/BaseMessage.hpp"

namespace ProtocolCraft
{
    class ClientboundContainerAckPacket : public BaseMessage<ClientboundContainerAckPacket>
    {
    public:
#if PROTOCOL_VERSION == 340 // 1.12.2
        static constexpr int packet_id = 0x11;
#elif PROTOCOL_VERSION == 393 || PROTOCOL_VERSION == 401 || PROTOCOL_VERSION == 404 // 1.13.X
        static constexpr int packet_id = 0x12;
#elif PROTOCOL_VERSION == 477 || PROTOCOL_VERSION == 480 || PROTOCOL_VERSION == 485 || PROTOCOL_VERSION == 490 || PROTOCOL_VERSION == 498 // 1.14.X
        static constexpr int packet_id = 0x12;
#elif PROTOCOL_VERSION == 573 || PROTOCOL_VERSION == 575 || PROTOCOL_VERSION == 578 // 1.15.X
        static constexpr int packet_id = 0x13;
#elif PROTOCOL_VERSION == 735 || PROTOCOL_VERSION == 736  // 1.16 or 1.16.1
        static constexpr int packet_id = 0x12;
#elif PROTOCOL_VERSION == 751 || PROTOCOL_VERSION == 753 || PROTOCOL_VERSION == 754 // 1.16.2, 1.16.3, 1.16.4, 1.16.5
        static constexpr int packet_id = 0x11;
#else
#error "Protocol version not implemented"
#endif
        static constexpr std::string_view packet_name = "Container Ack";

        virtual ~ClientboundContainerAckPacket() override
        {

        }

        void SetContainerId(const char container_id_)
        {
            container_id = container_id_;
        }

        void SetUid(const short uid_)
        {
            uid = uid_;
        }

        void SetAccepted(const bool accepted_)
        {
            accepted = accepted_;
        }

        char GetContainerId() const
        {
            return container_id;
        }

        short GetUid() const
        {
            return uid;
        }

        bool GetAccepted() const
        {
            return accepted;
        }

    protected:
        virtual void ReadImpl(ReadIterator &iter, size_t &length) override
        {
            container_id = ReadData<char>(iter, length);
            uid = ReadData<short>(iter, length);
            accepted = ReadData<bool>(iter, length);
        }

        virtual void WriteImpl(WriteContainer &container) const override
        {
            WriteData<char>(container_id, container);
            WriteData<short>(uid, container);
            WriteData<bool>(accepted, container);
        }

        virtual const nlohmann::json SerializeImpl() const override
        {
            nlohmann::json output;

            output["container_id"] = container_id;
            output["uid"] = uid;
            output["accepted"] = accepted;

            return output;
        }

    private:
        char container_id;
        short uid;
        bool accepted;
    };
} //ProtocolCraft
#endif
